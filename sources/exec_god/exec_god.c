/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_god.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:58:44 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/25 12:11:47 by jthuysba         ###   ########.fr       */
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

int	setup_cmd(t_cmd *cmd, t_list *token, t_exec *data)
{
	(void) data;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->cmd = get_cmd(token);
	set_fd(cmd, token);
	printf("out=%d,in=%d\n",cmd->fd_out, cmd->fd_in);
	// print_list(cmd->cmd);
	// printf("\n");
	return (0);
}

int	set_pipe(t_cmd *cmd, t_exec *data)
{
	
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
		setup_cmd(&(data->cmd[i]), elem, data);
		i++;
		while (elem && elem->type != PIPE)
			elem = elem->next;
		if (elem && elem->type == PIPE)
		{
			set_pipe(&(data->cmd[i]), data);
			elem = elem->next;
		}
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