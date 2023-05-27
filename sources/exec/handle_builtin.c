/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:56:53 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/27 19:49:02 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

int	is_builtin(t_list **cmd)
{
	if (ft_strncmp((*cmd)->content, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp((*cmd)->content, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp((*cmd)->content, "env", 3) == 0)
		return (1);
	else if (ft_strncmp((*cmd)->content, "exit", 4) == 0)
		return (1);
	else if (ft_strncmp((*cmd)->content, "export", 6) == 0)
		return (1);
	else if (ft_strncmp((*cmd)->content, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp((*cmd)->content, "unset", 5) == 0)
		return (1);
	return (0);
}

int	simple_builtin(t_cmd *cmd, t_exec *data)
{
	int	tmp_in;
	int	tmp_out;

	tmp_in = dup(STDIN_FILENO);
	tmp_out = dup(STDOUT_FILENO);
	dup2(cmd->fd_in, STDIN_FILENO);
	dup2(cmd->fd_out, STDOUT_FILENO);
	if (data->nb_pipes > 0)
		close_all(data, data->nb_pipes - 1);
	if (is_heredoc(cmd) == 1)
	{
		heredoc(cmd->cmd, data->env, cmd);
		return (0);
	}
	exec_builtin(cmd->cmd);
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
	close(tmp_in);
	close(tmp_out);
	return (0);
}

int	fork_builtin(t_cmd *cmd, t_exec *data)
{
	cmd->pid= fork();
	if (cmd->pid < 0)
		return (1);
	if (cmd->pid == 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		close_all(data, data->nb_pipes - 1);
		exec_builtin(cmd->cmd);
		exit(1);
	}
	return (0);
}
