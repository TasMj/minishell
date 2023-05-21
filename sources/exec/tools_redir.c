/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 23:12:13 by tas               #+#    #+#             */
/*   Updated: 2023/05/22 00:17:23 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

char	*get_file_name(t_list **list_token, char *c)
{
	t_list	*tmp;

	tmp = *list_token;
	while ((*list_token) != NULL)
	{
		if (ft_strcmp((*list_token)->content, c) == 0 && (*list_token)->next != NULL)
			return ((*list_token)->next->content);
		(*list_token) = (*list_token)->next;
	}
	(*list_token) = tmp;
	return (NULL);
}

char	*cmd_before_redir(t_list **list_token, t_redir *s)
{
	t_list	*tmp;

	tmp = *list_token;
	s->cmd = "";
	while ((*list_token) && (*list_token)->type == 0)
	{
		s->cmd = ft_strjoin_mod(s->cmd, (*list_token)->content, 0);
		if ((*list_token)->next->type == 0)
			s->cmd = ft_strjoin_mod(s->cmd, " ", 1);
		(*list_token) = (*list_token)->next;
	}
	(*list_token) = tmp;
	return (s->cmd);
}

void	init_redir(t_redir *s, t_list **list_token, char **env, char *c)
{
	char	*args;
	t_path	p;
	t_list	*tmp;

	tmp = *list_token;
	ft_memset(&p, 0, sizeof(t_path));
	s->file_name = ft_strdup_size(get_file_name(list_token, c), ft_strlen(get_file_name(list_token, c)));
	*list_token = tmp;
	args = ft_strdup_size(cmd_before_redir(list_token, s), ft_strlen(cmd_before_redir(list_token, s)));
	s->token_arg = ft_split(args, ' ');
	free(args);
	s->path_cmd = find_path(env, s->token_arg[0], p);
	*list_token = tmp;
}

void	free_redir(t_redir *redir)
{
	if (redir->cmd)
		free(redir->cmd);
	if (redir->file_name)
		free(redir->file_name);
	if (redir->path_cmd)
		free(redir->path_cmd);
	if (redir->token_arg)
		free_tab(redir->token_arg);
}
