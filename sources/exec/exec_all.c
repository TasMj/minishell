/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:38:07 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/26 14:47:56 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

int	is_heredoc(t_cmd *cmd)
{
	t_list	*elem;

	elem = *cmd->cmd;
	while (elem)
	{
		if (elem->type == HEREDOC)
			return (1);
		elem = elem->next;
	}
	return (0);
}

// Exec la commande cmd avec ses fd d'entree et sortie assignes
int	exec_cmd(t_cmd *cmd, t_exec *data)
{
	cmd->tab = lst_to_tab(cmd->cmd);
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (1);
	if (cmd->pid == 0)
	{
		print_list(cmd->cmd);
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		// if (data->nb_pipes > 0)
		// 	close_all(data, data->nb_pipes - 1);
		close(3);
		close(4);
		if (exec_builtin(cmd->cmd) == 1)
			return (0);
		if (is_heredoc(cmd) == 1)
		{
			heredoc(cmd->cmd, data->env);
			return (0);
		}
		execve(cmd->path, cmd->tab, data->env);
	}
	return (0);
}

int	exec_all(t_exec *data)
{
	int	i;

	i = 0;
	printf("nb_cmd=%d\n", data->nb_cmd);
	while (i < data->nb_cmd)
	{
		printf("i=%d\n", i);
		exec_cmd(&(data->cmd[i]), data);
		if (i != data->nb_pipes && data->nb_pipes > 0)
			close(data->fd[i][1]);
		close(3);
		close(4);
		waitpid(data->cmd[i].pid, NULL, 0);
		free_tab(data->cmd[i].tab);
		i++;
	}
	return (0);
}
