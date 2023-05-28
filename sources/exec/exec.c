/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:58:44 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/28 15:09:55 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

// Retourne le nombre de commandes
int	nb_cmd(t_list *token)
{
	int	count;

	count = 0;
	if (token->type == WORD)
		count++;
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
	cmd->path = find_path(data->env, (*cmd->cmd)->content);
	set_pipe(cmd, data);
	set_fd(cmd, elem);
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
		data->cmd[i].data = data;
		data->cmd[i].pid = -1;
		data->cmd[i].tmp_in = 0;
		data->cmd[i].tmp_out = 0;
		set_cmd(&data->cmd[i], data, elem);
		i++;
		while (elem && elem->type != PIPE)
			elem = elem->next;
		if (elem && elem->type == PIPE)
			elem = elem->next;
	}
	return (0);
}

int	exec(t_list **token, t_list **env)
{
	t_exec	data;
	
	data.token = token;
	data.env = lst_to_tab(env);
	setup_pipes(&data);
	setup_cmds(&data);

	exec_all(&data);

	clean_all(&data);
	return (0);
}