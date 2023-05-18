/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:01:28 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/18 15:41:18 by jthuysba         ###   ########.fr       */
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
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		if (data->nb_pipes > 0)
			close_all(data, data->nb_pipes - 1);
		execve(cmd->path, cmd->cmd, data->env);
	}
	return (0);
}

int	is_word(char *tok)
{
	if (check_redir_in(tok[0]) == 1 || check_redir_out(tok[0]) == 1 ||
		check_append(tok) == 1 || check_heredoc(tok) == 1)
		return (0);
	return (1);
}

int	size_to_op(char **cmd)
{
	int	i;

	i = 0;
	while (is_word(cmd[i]) == 1)
		i++;
	return (i);
}

char	**get_cut_cmd(char **cmd)
{
	char	**ex_cmd;
	int		i;

	ex_cmd = malloc(sizeof(char *) * size_to_op(cmd) + 1);
	i = 0;
	while (is_word(cmd[i]) == 1)
	{
		ex_cmd[i] = ft_strdup_size(cmd[i], ft_strlen(cmd[i]));
		i++;
	}
	ex_cmd[i] = 0;
	return (ex_cmd);
}

int	exec_stdin(t_cmd *cmd, t_exec *data)
{
	char	**cut_cmd;

	cut_cmd = get_cut_cmd(cmd->cmd);
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (1);
	if (cmd->pid == 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_in);
		if (data->nb_pipes > 0)
			close_all(data, data->nb_pipes - 1);
		execve(cmd->path, cut_cmd, data->env);
	}
	return (0);
}

int	exec_type(t_cmd *cmd, t_exec *data)
{
	if (cmd->type == WORD)
		exec_cmd(cmd, data);
	else if (cmd->type == STDIN)
		exec_stdin(cmd, data);
	return (0);
}

int	exec(t_exec *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd)
	{
		// if (exec_cmd(&(data->cmd[i]), data) != 0)
		// 	return (1);
		
		exec_type(&(data->cmd[i]), data);
		
		if (i != data->nb_pipes)
			close(data->cmd[i].fd_out);
		waitpid(data->cmd[i].pid, NULL, 0);
		i++;
	}
	return (0);
}

int	exec_all(t_list *token, char **env)
{
	t_exec	data;

	data.token = &token;
	data.env = env;
	setup_pipes(&data);
	setup_cmd(&data);
	// printf(">>>HERE<<<\n");
	if (exec(&data) == 1)
	{
		clean_all(&data);
		return (1);
	}
	clean_all(&data);
	return (0);
}
