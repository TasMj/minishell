/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:38:07 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/29 23:59:31 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
// #include "heredoc.h"

// int	is_heredoc(t_cmd *cmd)
// {
// 	t_list	*elem;

// 	elem = *cmd->cmd;
// 	while (elem)
// 	{
// 		if (elem->type == HEREDOC)
// 			return (1);
// 		elem = elem->next;
// 	}
// 	return (0);
// }

// // Exec la commande cmd avec ses fd d'entree et sortie assignes
// int	exec_cmd(t_cmd *cmd, t_exec *data)
// {
// 	cmd->tab = lst_to_tab(cmd->cmd);
// 	cmd->pid = fork();
// 	if (cmd->pid < 0)
// 		return (1);
// 	if (cmd->pid == 0)
// 	{
// 		dup2(cmd->fd_in, STDIN_FILENO);
// 		dup2(cmd->fd_out, STDOUT_FILENO);
// 		if (data->nb_pipes > 0)
// 			close_all(data, data->nb_pipes - 1);
// 		fprintf(stderr, "%i\n", __LINE__);
// 		if (is_heredoc(cmd) == 1)
// 		{
// 			heredoc(cmd->cmd, data->env, cmd);
// 			// exit(0);
// 		}
// 		fprintf(stderr, "%i\n", __LINE__);
// 		if (is_path(cmd) == 1)
// 		{
// 			if (access((*cmd->cmd)->content, F_OK | X_OK) != 0)
// 			{
// 				printf("minishell: %s: Not a directory\n", (*cmd->cmd)->content);
// 				return (1);
// 			}
// 			if (execve((*cmd->cmd)->content, cmd->tab, data->env) < 0)
// 				exit(1);
// 		}
// 		if (cmd->path == NULL)
// 			return (err_msg(2));
// 		if (execve(cmd->path, cmd->tab, data->env) < 0)
// 				exit(1);
// 	}
// 	return (0);
// }

// // int	exec_cmd(t_cmd *cmd, t_exec *data)
// // {
// // 	cmd->tab = lst_to_tab(cmd->cmd);
// // 	cmd->pid = fork();
// // 	if (cmd->pid < 0)
// // 		return (1);
// // 	if (cmd->pid == 0)
// // 	{
// // 		dup2(cmd->fd_in, STDIN_FILENO);
// // 		dup2(cmd->fd_out, STDOUT_FILENO);
// // 		if (data->nb_pipes > 0)
// // 			close_all(data, data->nb_pipes - 1);
// // 		if (is_heredoc(cmd) == 1)
// // 		{
// // 			heredoc(cmd->cmd, data->env, cmd);
// // 			// exit(0);
// // 			return (0);
// // 		}
// // 		if (is_path(cmd) == 1)
// // 		{
// // 			if (execve((*cmd->cmd)->content, cmd->tab, data->env) < 0)
// // 				exit(1);
// // 		}
// // 		if (execve(cmd->path, cmd->tab, data->env) < 0)
// // 			exit(1);
// // 	}
// // 	return (0);
// // }

// int	redirect_heredoc(t_cmd *cmd, t_exec *data)
// {
// 	// cmd->tmp_in = dup(STDIN_FILENO);
// 	// cmd->tmp_out = dup(STDOUT_FILENO);
// 	// dup2(cmd->fd_in, STDIN_FILENO);
// 	// dup2(cmd->fd_out, STDOUT_FILENO);
// 	// if (data->nb_pipes > 0)
// 	// 	close_all(data, data->nb_pipes - 1);
// 	heredoc(cmd->cmd, data->env, cmd);
// 	fprintf(stderr,"ghjk\n");
// 	close(cmd->fd_out);
// 	close(cmd->fd_in);
// 	// dup2(cmd->tmp_in, STDIN_FILENO);
// 	// dup2(cmd->tmp_out, STDOUT_FILENO);
// 	// close(cmd->tmp_in);
// 	// close(cmd->tmp_out);
// 	return (0);
// }

// int	exec_all(t_exec *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->nb_cmd)
// 	{
// 		if (is_builtin(data->cmd[i].cmd) == 1)
// 		{
// 			if (data->nb_cmd == 1)
// 				simple_builtin(&data->cmd[i], data);
// 			else
// 				fork_builtin(&data->cmd[i], data);
// 		}
// 		else
// 		{
// 			if ((data->cmd[i].fd_out != STDOUT_FILENO 
// 			|| data->cmd[i].fd_in != STDIN_FILENO)
// 			&& is_heredoc(&data->cmd[i]) == 1)
// 			{
// 				printf("here\n");
// 				redirect_heredoc(&data->cmd[i], data);
// 			}
// 			else
// 				exec_cmd(&(data->cmd[i]), data);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (i < data->nb_cmd)
// 	{
// 		close_all(data, data->nb_pipes - 1);
// 		if (data->cmd[i].pid != -1)
// 			waitpid(data->cmd[i].pid, NULL, 0);
// 		if (is_builtin(data->cmd[i].cmd) == 0)
// 			free_tab(data->cmd[i].tab);
// 		i++;
// 	}
// 	return (0);
// }
