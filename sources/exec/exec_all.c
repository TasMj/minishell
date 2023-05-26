/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:38:07 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/26 17:57:40 by jthuysba         ###   ########.fr       */
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

int	is_path(t_cmd *cmd)
{
	int	i;

	i = 0;
	while ((*cmd->cmd)->content[i])
	{
		if ((*cmd->cmd)->content[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

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

// Exec la commande cmd avec ses fd d'entree et sortie assignes
int	exec_cmd(t_cmd *cmd, t_exec *data)
{
	cmd->tab = lst_to_tab(cmd->cmd);
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (1);
	if (cmd->pid == 0)
	{
		// print_list(cmd->cmd);
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		if (data->nb_pipes > 0)
			close_all(data, data->nb_pipes - 1);

		// if (is_builtin(cmd->cmd) == 1)
		// {
		// 	exec_builtin(cmd->cmd);
		// 	return (0);
		// }

		if (is_heredoc(cmd) == 1)
		{
			heredoc(cmd->cmd, data->env);
			return (0);
		}
		if (is_path(cmd) == 1)
		{
			if (execve((*cmd->cmd)->content, cmd->tab, data->env) < 0)
				return (1);
		}
		if (execve(cmd->path, cmd->tab, data->env) < 0)
			return (1);
	}
	return (0);
}

int	handle_builtin(t_cmd *cmd, t_exec *data)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (1);
	if (cmd->pid == 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		if (data->nb_pipes > 0)
			close_all(data, data->nb_pipes - 1);
		if (is_heredoc(cmd) == 1)
		{
			heredoc(cmd->cmd, data->env);
			return (0);
		}
		exec_builtin(cmd->cmd);
	}
	return (0);
}

int	exec_all(t_exec *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd)
	{
		if (is_builtin(data->cmd[i].cmd) == 1)
			handle_builtin(&data->cmd[i], data);
		else
			exec_cmd(&(data->cmd[i]), data);
		if (i != data->nb_pipes && data->nb_pipes > 0)
			close(data->fd[i][1]);
		waitpid(data->cmd[i].pid, NULL, 0);
		if (is_builtin(data->cmd[i].cmd) == 0)
			free_tab(data->cmd[i].tab);
		i++;
	}
	return (0);
}
