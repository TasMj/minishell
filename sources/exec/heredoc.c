/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:34:23 by tas               #+#    #+#             */
/*   Updated: 2023/05/26 17:10:41 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

char	*cmd_before_heredoc(t_list **list_token, t_heredoc *h)
{
	t_list	*tmp;

	tmp = *list_token;
	h->cmd = "";
	while ((*list_token) && (*list_token)->type == 0)
	{
		h->cmd = ft_strjoin_mod(h->cmd, (*list_token)->content, 0);
		if ((*list_token)->next->type == 0)
			h->cmd = ft_strjoin_mod(h->cmd, " ", 1);
		(*list_token) = (*list_token)->next;
	}
	(*list_token) = tmp;
	return (h->cmd);
}

int	heredoc(t_list **token, char **env)
{
	t_heredoc	*h;
	t_list		*first_cmd;
	char		*args;

	h = malloc(sizeof(t_heredoc));
	first_cmd = *token;
	args = ft_strdup_size(cmd_before_heredoc(token, h), \
	ft_strlen(cmd_before_heredoc(token, h)));
	while (*token)
	{
		if (check_heredoc((*token)->content) == 1 && (*token)->next == NULL)
			break ;
		else if (check_heredoc((*token)->content) == 1)
		{
			h->path_cmd = find_path(env, first_cmd->content);
			h->token_arg = ft_split(args, ' ');
			h->delimiteur = ft_strdup_size((*token)->next->content, \
			ft_strlen((*token)->next->content));
			free(args);
			heredoc_process(h, env);
		}
		(*token) = (*token)->next;
	}
	free(args);
	free_heredoc(h);
	(*token) = first_cmd;
	return (0);
}

int	parent_process(t_heredoc *h, char **env)
{
	close(h->tube[1]);
	if (waitpid(h->pid, NULL, 0) == -1)
		exit(EXIT_FAILURE);
	dup2(h->tube[0], STDIN_FILENO);
	if (execve(h->path_cmd, h->token_arg, env) == -1)
		exit(EXIT_FAILURE);
	close(h->tube[0]);
	exit(EXIT_SUCCESS);
}

void
ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return ;
	(void)write(fd, str, ft_strlen(str));
}

int	heredoc_process(t_heredoc *h, char **env)
{
	char	*stockage;

	if (pipe(h->tube) == -1)
		exit(EXIT_FAILURE);
	h->pid = fork();
	if (h->pid == -1)
		exit(EXIT_FAILURE);
	if (h->pid == 0)
	{
		close(h->tube[0]);
		while (1)
		{
			stockage = readline("heredoc> ");
			if (ft_strcmp(stockage, h->delimiteur) == 0)
				break ;
			else
			{
				ft_putstr_fd(stockage, h->tube[1]);
				ft_putstr_fd("\n", h->tube[1]);
			}
			// else if (write(h->tube[1], ft_strjoin_mod(stockage, "\n", 1), \
			// ft_strlen(stockage) + 1) == -1)
			// 	exit(EXIT_FAILURE);
		}
		close(h->tube[1]);
		free(stockage);
		exit(EXIT_SUCCESS);
	}
	else
		parent_process(h, env);
	return (0);
}
