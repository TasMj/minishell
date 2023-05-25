/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_god.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:58:44 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/25 12:29:52 by jthuysba         ###   ########.fr       */
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
		add_list(lst, elem->content, 0);
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

int	set_cmds(t_exec *data)
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
		// ft_memset(&(data->cmd[i]), 0, sizeof(t_cmd));
		data->cmd[i].id = i;
		data->cmd[i].cmd = get_cmd(elem);
		set_pipe(&(data->cmd[i]), data);
		set_fd(&(data->cmd[i]), elem);
		printf("in=%d\nout=%d\n", data->cmd[i].fd_in, data->cmd[i].fd_out);
		i++;
		while (elem && elem->type != PIPE)
			elem = elem->next;
		if (elem && elem->type == PIPE)
			elem = elem->next;
	}
	return (0);
}

int	exec_god(t_exec *data)
{
	setup_pipes(data);
	set_cmds(data);
	close_fd(data);
	clean_all(data);
	return (0);
}