/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:02:44 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/22 01:11:22 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	exec_stdin(t_cmd *cmd, t_exec *data)
// {
// 	char	**cut_cmd;

// 	cut_cmd = get_cut_cmd(cmd->cmd);
// 	cmd->pid = fork();
// 	if (cmd->pid < 0)
// 		return (1);
// 	if (cmd->pid == 0)
// 	{
// 		dup2(cmd->fd_in, STDIN_FILENO);
// 		dup2(cmd->fd_out, STDOUT_FILENO);
// 		close(cmd->fd_in);
// 		if (data->nb_pipes > 0)
// 			close_all(data, data->nb_pipes - 1);
// 		execve(cmd->path, cut_cmd, data->env);
// 	}
// 	return (0);
// }

// int	exec_stdout(t_list **cmd, char *file, t_exec *data)
// {
	
// 	return (0);
// }
