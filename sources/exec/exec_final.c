/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_final.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:01:28 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/16 16:36:35 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Exec la commande cmd avec ses fd d'entree et sortie assignes
int	exec_cmd(t_cmd *cmd, t_exec *data)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (1);
	if (cmd->pid == 0)
	{
		// printf("\ncmd = %s\nin = %d\nout = %d\nid = %d\n\n", cmd->cmd[0], cmd->fd_in, cmd->fd_out, cmd->id);
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		if (data->nb_pipes > 0)
			close_all(data, data->nb_pipes - 1);
		execve(cmd->path, cmd->cmd, data->env);
	}
	// printf("here\n");
	return (0);
}

int	exec(t_exec *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd)
	{
		if (exec_cmd(&(data->cmd[i]), data) != 0)
			return (1);
		if (i != data->nb_pipes)
			close(data->cmd[i].fd_out);
		waitpid(data->cmd[i].pid, NULL, 0);
		i++;
	}
	return (0);
}

// Exec simple si pas d'operateurs
int	single_exec(t_exec *data)
{
	char	**cmd;
	int	pid;
	t_path	p;

	cmd = get_cmd(*data->token);
	pid = fork();
	ft_memset(&p, 0, sizeof(t_path));
	if (pid < 0)
		return (free_tab(cmd), 1);
	if (pid == 0)
		execve(find_path(data->env, cmd[0], p), cmd, data->env);
	waitpid(pid, NULL, 0);
	return (0);
}

int	exec_all(t_list *token, char **env)
{
	t_exec	data;

	data.token = &token;
	data.env = env;
	if (count_pipes(token) == 0)
	{
		if (single_exec(&data))
			return (1);
		return (0);
	}
	setup_pipes(&data);
	setup_cmd(&data);
	if (exec(&data) == 1)
	{
		clean_all(&data);
		return (1);
	}
	clean_all(&data);
	return (0);
}
