/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:01:28 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/22 01:15:21 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

char	**lst_to_tab(t_list **lst)
{
	t_list	*elem;
	char	**tab;
	int	i;

	elem = *lst;
	tab = malloc(sizeof(char *) * ft_lstsize(*lst));
	if (!tab)
		return (NULL);
	i = 0;
	while (elem)
	{
		tab[i] = ft_strdup_size(elem->content, ft_strlen(elem->content));
		elem = elem->next;
		i++;
	}
	tab[i] = 0;
	return (tab);
}

// Exec la commande cmd avec ses fd d'entree et sortie assignes
int	exec_cmd(t_cmd *cmd, t_exec *data)
{
	char	**tab;

	tab = lst_to_tab(cmd->cmd);
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (1);
	if (cmd->pid == 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		if (data->nb_pipes > 0)
			close_all(data, data->nb_pipes - 1);
		if (exec_builtin(cmd->cmd) == 1)
			return (0);
		execve(cmd->path, tab, data->env);
		free_tab(tab);
	}
	return (0);
}

t_list	**get_trunc_cmd(t_list *tok)
{
	t_list	**lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	*lst = NULL;
	while (tok && tok->type == WORD)
	{
		add_list(lst, tok->content, tok->flag_space);
		tok = tok->next;
	}
	get_type(lst);
	return (lst);
}

char	*get_file(t_list *lst)
{
	return (ft_lstlast(lst)->content);
}

int	exec_op(t_cmd *cmd, t_exec *data)
{
	(void) data;
	
	t_list	**trunc_cmd;
	t_list	*elem;
	char	*file;
	int	fd;

	trunc_cmd = get_trunc_cmd(*cmd->cmd);
	file = get_file(*cmd->cmd);
	elem = *cmd->cmd;
	(void) file;
	while (elem)
	{
		if (elem->type != WORD && elem->next)
		{
			fd = open(elem->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				return (1);
			close(fd);
		}
		elem = elem->next;
	}
	free(file);
	free_list(trunc_cmd);
	return (0);
}

int	exec_global(t_exec *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd)
	{
		// if (check_op() == 1)
		exec_op(&(data->cmd[i]), data);
		exec_cmd(&(data->cmd[i]), data);
		if (i != data->nb_pipes)
			close(data->cmd[i].fd_out);
		waitpid(data->cmd[i].pid, NULL, 0);
		i++;
	}
	return (0);
}

int	exec_all(t_list *token, char **env)
{
	t_exec	data;

	data.token = &token;
	data.env = env;
	setup_pipes(&data);
	setup_cmd(&data);
	if (exec_global(&data) == 1)
	{
		clean_all(&data);
		return (1);
	}
	clean_all(&data);
	return (0);
}
