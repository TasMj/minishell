/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:38:07 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/25 14:41:29 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Exec la commande cmd avec ses fd d'entree et sortie assignes
int	exec_cmd(t_cmd *cmd, t_exec *data)
{
	char	**tab;

	tab = lst_to_tab(cmd->cmd);
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (free_tab(tab), 1);
	if (cmd->pid == 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		if (data->nb_pipes > 0)
			close_all(data, data->nb_pipes - 1);
		if (exec_builtin(cmd->cmd) == 1)
			return (free_tab(tab), 0);
		if (execve(cmd->path, tab, data->env) == -1)
			return (free_tab(tab), 1);
	}
	return (free_tab(tab), 0);
}

int	exec_all(t_exec *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd)
	{
		if (exec_cmd(&(data->cmd[i]), data) != 0)
			return (1);
		if (i != data->nb_pipes)
			close(data->fd[i][1]);
		waitpid(data->cmd[i].pid, NULL, 0);
		i++;
	}
	return (0);
}
