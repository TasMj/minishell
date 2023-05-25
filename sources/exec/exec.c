/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:58:44 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/25 16:41:17 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

// Retourne le nombre de commandes
int	nb_cmd(t_list *token)
{
	int	count;

	count = 1;
	while (token)
	{
		if (token->type == PIPE)
			count++;
		token = token->next;
	}
	return (count);
}

t_list	**get_cmd(t_list *token)
{
	t_list	**lst;
	t_list	*elem;

	elem = token;
	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	*lst = NULL;
	while (elem && elem->type == WORD)
	{
		add_list(lst, elem->content, elem->flag_space);
		elem = elem->next;
	}
	return (lst);
}

// Setup fd in et out pour chaque commande
void	set_pipe(t_cmd *cmd, t_exec *data)
{
	if (data->nb_cmd == 1)
	{
		cmd->fd_in = STDIN_FILENO;
		cmd->fd_out = STDOUT_FILENO;
	}
	else if (cmd->id == 0)
	{
		cmd->fd_in = STDIN_FILENO;
		cmd->fd_out = data->fd[0][1];	
	}
	else if (cmd->id == data->nb_pipes)
	{
		cmd->fd_in = data->fd[cmd->id - 1][0];
		cmd->fd_out = STDOUT_FILENO;
	}
	else
	{
		cmd->fd_in = data->fd[cmd->id - 1][0];
		cmd->fd_out = data->fd[cmd->id][1];
	}
}

int	set_cmd(t_cmd *cmd, t_exec *data, t_list *elem)
{
	cmd->cmd = get_cmd(elem);
	if (!cmd->cmd)
		return (1);
	cmd->path = find_path(data->env, (*cmd->cmd)->content);
	if (!cmd->path)
		return (1);
	set_pipe(cmd, data);
	if (set_fd(cmd, elem) != 0)
		return (1);
	if (elem->type == HEREDOC)
		cmd->heredoc = ft_strdup(elem->next->content);
	return (0);
}

int	setup_cmds(t_exec *data)
{
	t_list	*elem;
	int	i;

	data->nb_cmd = nb_cmd(*data->token);
	data->cmd = malloc(sizeof(t_cmd) * data->nb_cmd);
	if (!data->cmd)
		return (1);
	i = 0;
	elem = *data->token;
	while (elem)
	{
		data->cmd[i].id = i;
		if (set_cmd(&(data->cmd[i]), data, elem) != 0)
			return (1);
		i++;
		while (elem && elem->type != PIPE)
			elem = elem->next;
		if (elem && elem->type == PIPE)
			elem = elem->next;
	}
	return (0);
}

int	exec(t_list **token, char **env)
{
	t_exec	data;

	data.token = token;
	data.env = env;
	if (setup_pipes(&data) != 0)
		return (clean_all(&data), 1);
	
	if (setup_cmds(&data) != 0)
		return (clean_all(&data), 1);

	if (exec_all(&data) != 0)
		return (clean_all(&data), 1);
	
	clean_all(&data);
	return (0);
}