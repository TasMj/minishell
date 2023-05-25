/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:20:11 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/25 11:46:12 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

// Setup fd in et out pour chaque commande
// void	set_fd(t_cmd *cmd, t_exec *data)
// {
// 	if (data->nb_pipes == 0)
// 	{
// 		cmd->fd_in = STDIN_FILENO;
// 		cmd->fd_out = STDOUT_FILENO;	
// 	}
// 	else if (cmd->id == 0)
// 	{
// 		cmd->fd_in = STDIN_FILENO;
// 		cmd->fd_out = data->fd[0][1];	
// 	}
// 	else if (cmd->id == data->nb_pipes)
// 	{
// 		cmd->fd_in = data->fd[cmd->id - 1][0];
// 		cmd->fd_out = STDOUT_FILENO;
// 	}
// 	else
// 	{
// 		cmd->fd_in = data->fd[cmd->id - 1][0];
// 		cmd->fd_out = data->fd[cmd->id][1];
// 	}
// 	// set_op_fd(cmd);
// }