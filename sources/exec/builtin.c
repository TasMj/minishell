/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:42:19 by tmejri            #+#    #+#             */
/*   Updated: 2023/06/30 11:01:53 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_list **list);
void	ft_pwd(void);

static int	exec_builtin(t_cmd *cmd)
{
	t_list	*tmp;
	int		ret;

	if (!cmd->cmd || ft_lstsize(*cmd->cmd) == 0)
		return (-1);
	ret = 0;
	tmp = *cmd->cmd;
	if (ft_strlen((*cmd->cmd)->content) == 2 && ft_strncmp((*cmd->cmd)->content, "cd", 2) == 0)
		ret = ft_cd(cmd);
	else if (ft_strlen((*cmd->cmd)->content) == 4 && ft_strncmp((*cmd->cmd)->content, "echo", 4) == 0)
		ret = ft_echo((*cmd->cmd)->content);
	else if (ft_strlen((*cmd->cmd)->content) == 3 && ft_strncmp((*cmd->cmd)->content, "env", 3) == 0)
		ret = ft_env((*cmd->cmd)->content);
	else if (ft_strlen((*cmd->cmd)->content) == 6 && ft_strncmp((*cmd->cmd)->content, "export", 6) == 0)
		ret = ft_export(cmd->cmd);
	else if (ft_strlen((*cmd->cmd)->content) == 3 && ft_strncmp((*cmd->cmd)->content, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strlen((*cmd->cmd)->content) == 5 && ft_strncmp((*cmd->cmd)->content, "unset", 5) == 0)
		ret = ft_unset(cmd->cmd);
	else
		return (1);
	if (ret != 0)
		return (1);
	*cmd->cmd = tmp;
	return (0);
}

void	dup_n_close(int tmp_in, int tmp_out)
{
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
	close(tmp_in);
	close(tmp_out);
}

int	handle_exit(t_cmd *cmd, t_minishell *data)
{
	if (ft_strcmp((*cmd->cmd)->content, "exit") == 0)
	{
		if (data->x->nb_cmd > 1)
			return (1);
		if (ft_lstsize(*(cmd->cmd)) == 1)
		{
			printf("exit\n");
			ft_exit(cmd->data);
		}
		else if (ft_lstsize(*(cmd->cmd)) > 1)
			ft_exit_code(cmd, data);
	}
	return (0);
}

int		bltin_dup_pipes(t_cmd *cmd, t_minishell *data)
{
	if (cmd->id == 0)
		dup2(data->x->pipe[0][1], STDOUT_FILENO);
	else if (cmd->id == data->x->nb_cmd - 1)
		dup2(data->x->pipe[data->x->nb_cmd - 2][0], STDIN_FILENO);
	else
	{
		dup2(data->x->pipe[cmd->id - 1][0], STDIN_FILENO);
		dup2(data->x->pipe[cmd->id][1], STDOUT_FILENO);
	}
	return (0);
}

int	handle_builtin(t_cmd *cmd, t_minishell *data)
{
	int	tmp_in;
	int	tmp_out;


	if (handle_exit(cmd, data) == 1)
		return (0);
	tmp_in = dup(STDIN_FILENO);
	tmp_out = dup(STDOUT_FILENO);
	if (data->x->nb_cmd > 1)
		bltin_dup_pipes(cmd, data);
	if (open_n_dup(cmd, data->x) != 0)
	{
		dup_n_close(tmp_in, tmp_out);
		printf("File open error (WIP)\n");
		return (1);
	}
	else
		if (exec_builtin(cmd) != 0)
			return (dup_n_close(tmp_in, tmp_out), 1);
	dup_n_close(tmp_in, tmp_out);
	return (0);
}