/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:01:28 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/21 20:12:39 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

int	len_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

t_list	**setup_built_lst(t_cmd *cmd)
{
	t_list	**lst;
	int	i;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	*lst = NULL;
	i = 0;
	while (cmd->cmd[i])
	{
		add_list(lst, cmd->cmd[i], 1);
		i++;
	}
	return (lst);
}

void	exec(t_cmd *cmd, t_exec *data)
{
	t_list	**built_lst;
	// (void) data;
	
	built_lst = setup_built_lst(cmd);
	// printf("%s\n", (*built_lst)->content);
	if (exec_builtin(built_lst) == 0)
		execve(cmd->path, cmd->cmd, data->env);
}

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
		// execve(cmd->path, cmd->cmd, data->env);
		exec(cmd, data);
	}
	return (0);
}

int	exec_type(t_cmd *cmd, t_exec *data)
{
	if (cmd->type == WORD)
		exec_cmd(cmd, data);
	else if (cmd->type == STDIN)
		exec_stdin(cmd, data);
	else if (cmd->type == STDOUT || cmd->type == APPEND)
		exec_stdout(cmd, data);
	else if (cmd->type == HEREDOC)
		heredoc(data->token, data->env);
	return (0);
}

int	exec_global(t_exec *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd)
	{
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
	if (exec_global(&data) == 1)
	{
		clean_all(&data);
		return (1);
	}
	clean_all(&data);
	return (0);
}
