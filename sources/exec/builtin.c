/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:42:19 by tmejri            #+#    #+#             */
/*   Updated: 2023/06/27 12:02:10 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_list **list);
void	ft_pwd(void);

int	exec_builtin(t_cmd *cmd, t_minishell *data)
{
	t_list	*tmp;

	if (!cmd->cmd || ft_lstsize(*cmd->cmd) == 0)
		return (-1);
	tmp = *cmd->cmd;
	if (ft_strlen((*cmd->cmd)->content) == 2 && ft_strncmp((*cmd->cmd)->content, "cd", 2) == 0)
		ft_cd(cmd->cmd);
	else if (ft_strlen((*cmd->cmd)->content) == 4 && ft_strncmp((*cmd->cmd)->content, "echo", 4) == 0)
		ft_echo(cmd->cmd);
	else if (ft_strlen((*cmd->cmd)->content) == 3 && ft_strncmp((*cmd->cmd)->content, "env", 3) == 0)
		ft_env(cmd->cmd);
	else if (ft_strlen((*cmd->cmd)->content) == 4 && ft_strncmp((*cmd->cmd)->content, "exit", 4) == 0)
		ft_exit(data);
	else if (ft_strlen((*cmd->cmd)->content) == 6 && ft_strncmp((*cmd->cmd)->content, "export", 6) == 0)
		ft_export(cmd->cmd);
	else if (ft_strlen((*cmd->cmd)->content) == 3 && ft_strncmp((*cmd->cmd)->content, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strlen((*cmd->cmd)->content) == 5 && ft_strncmp((*cmd->cmd)->content, "unset", 5) == 0)
		ft_unset(cmd->cmd);
	else
		return (1);
	*cmd->cmd = tmp;
	return (0);
}

int	handle_builtin(t_cmd *cmd, t_minishell *data)
{
	int	tmp_in;
	int	tmp_out;

	tmp_in = dup(STDIN_FILENO);
	tmp_out = dup(STDOUT_FILENO);
	// dup_pipe(cmd, data->x);
	if (data->x->nb_cmd > 1)
	{
		if (data->x->nb_cmd == 1)
			return (0);
		if (cmd->id == 0)
			dup2(data->x->pipe[0][1], STDOUT_FILENO);
		else if (cmd->id == data->x->nb_cmd - 1)
		{
			dup2(data->x->pipe[data->x->nb_cmd - 2][0], STDIN_FILENO);
		}
		else
		{
			dup2(data->x->pipe[cmd->id - 1][0], STDIN_FILENO);
			dup2(data->x->pipe[cmd->id][1], STDOUT_FILENO);
		}
	}
	open_n_dup(cmd, data->x);
	exec_builtin(cmd, data);
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
	close(tmp_in);
	close(tmp_out);
	return (0);
}