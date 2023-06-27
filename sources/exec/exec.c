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
		open_n_dup(cmd, data->x);

		// if (exec_it(cmd, data) != 0)
		// 	exit(1);
		// execlp("pwd", "pwd", NULL);
		exec_it(cmd , data);
	}
	return (0);
}

/* Execute les commandes */
static int	go_exec(t_xek *x, t_minishell *data)
{
	int	i;
	int	ret;
	
	/* On lance un process pour chaque commande */
	i = 0;
	// printf("xnbmc=%d\n", x->nb_cmd);
	while (i < x->nb_cmd)
	{
		// launch_process(&(x->cmd[i]), data);
		if (is_builtin(&(x->cmd[i])) == 0)
		{
			launch_process(&(x->cmd[i]), data);
		}
		else
		{

			handle_builtin(&(x->cmd[i]), data);
		}
		i++;
	}
	close_all(x);
	i = 0;
	while (i < x->nb_cmd)
	{
		waitpid(x->cmd[i].pid, &ret, WUNTRACED);
		// execlp("pwd", "pwd", NULL);
		if (WIFEXITED(ret))
		{
			x->cmd->data->code_err = WEXITSTATUS(ret);
		}
		else
		{

			x->cmd->data->code_err = WTERMSIG(ret) + 128;
			if (x->cmd->data->code_err == 139)
				printf("Segmentation Fault BOOM !\n");
			// else
				// printf("Interrupted with signal %d\n", x->cmd->data->code_err);
		}
		i++;
	}
	set_signal();
	return (0);
}

/* Execute les tokens
-> cat < file | wc -l > file2 */
int	we_exec(t_minishell *data)
{
	int	i;


	i = 0;
	data->x = malloc(sizeof(t_xek));
	ft_memset(data->x, 0, sizeof(t_xek));
	if (prep_cmd(data) == 1)
	{
		while (i < data->x->nb_cmd)
		{
			free_cmd(&(data->x->cmd[i]));
			i++;
		}
		free(data->x->cmd);
		free(data->x);
		return (1);
	}
	open_pipes(data);
	exec_heredoc(data);
	go_exec(data->x, data);
	destroy_exec(data->x);
	return (0);
}
