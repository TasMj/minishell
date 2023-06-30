/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:57:13 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/30 01:18:40 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (ft_strlen((*cmd->cmd)->content) == 2 && ft_strncmp((*cmd->cmd)->content, "cd", 2) == 0)
		return (1);
	else if (ft_strlen((*cmd->cmd)->content) == 4 && ft_strncmp((*cmd->cmd)->content, "echo", 4) == 0)
		return (1);
	else if (ft_strlen((*cmd->cmd)->content) == 3 && ft_strncmp((*cmd->cmd)->content, "env", 3) == 0)
		return (1);
	else if (ft_strlen((*cmd->cmd)->content) == 4 && ft_strncmp((*cmd->cmd)->content, "exit", 4) == 0)
		return (1);
	else if (ft_strlen((*cmd->cmd)->content) == 6 && ft_strncmp((*cmd->cmd)->content, "export", 6) == 0)
		return (1);
	else if (ft_strlen((*cmd->cmd)->content) == 3 && ft_strncmp((*cmd->cmd)->content, "pwd", 3) == 0)
		return (1);
	else if (ft_strlen((*cmd->cmd)->content) == 5 && ft_strncmp((*cmd->cmd)->content, "unset", 5) == 0)
		return (1);
	return (0);
}

/* On lance un process pour chaque commande */
static int	launch_process(t_cmd *cmd, t_minishell *data)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (1);
	if (cmd->pid == 0)
	{
		dup_pipe(cmd, data->x);
		if (open_n_dup(cmd, data->x) != 0)
		{
			// destroy_exec(data->x);
			ft_exit(data);
		}
		exec_it(cmd , data);
	}
	return (0);
}

int	wait_child(t_xek *x)
{
	int	i;
	int	ret;

	close_all(x);
	i = 0;
	ret = 0;
	while (i < x->nb_cmd)
	{
		waitpid(x->cmd[i].pid, &ret, WUNTRACED);
		if (WIFEXITED(ret))
			x->cmd->data->code_err = WEXITSTATUS(ret);
		else
		{
			x->cmd->data->code_err = WTERMSIG(ret) + 128;
			if (x->cmd->data->code_err == 139)
				err_write("Segmentation fault error\n");
				// printf("Segmentation Fault BOOM !\n");
			// else
				// printf("Interrupted with signal %d\n", x->cmd->data->code_err);
		}
		i++;
	}
	return (0);
}

/* Execute les commandes */
static int	go_exec(t_xek *x, t_minishell *data)
{
	int	i;
	
	/* On lance un process pour chaque commande */
	i = 0;
	// signal_ignore();
	while (i < x->nb_cmd)
	{
		if (is_builtin(&(x->cmd[i])) == 0)
			launch_process(&(x->cmd[i]), data);
		else
			if (handle_builtin(&(x->cmd[i]), data) != 0)
				return (wait_child(x), 1);
		i++;
	}
	wait_child(x);
	set_signal();
	return (0);
}

/* Execute les tokens
-> cat < file | wc -l > file2 */
int	we_exec(t_minishell *data)
{
	data->x = malloc(sizeof(t_xek));
	ft_memset(data->x, 0, sizeof(t_xek));
	if (prep_cmd(data) == 1)
		return (destroy_exec(data->x), 1);
	open_pipes(data);
	if (exec_heredoc(data) != 0)
	{
		data->code_err = 1;
		return (destroy_exec(data->x), 1);
	}
	if (go_exec(data->x, data) != 0)
	{
		data->code_err = 1;
		return (destroy_exec(data->x), 1);
	}
	destroy_exec(data->x);
	return (0);
}
