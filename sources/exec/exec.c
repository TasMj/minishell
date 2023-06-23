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

/* On lance un process pour chaque commande */
static int	launch_process(t_cmd *cmd, t_xek *x)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (1);
	if (cmd->pid == 0)
	{
		dup_pipe(cmd, x);
		open_n_dup(cmd, x);

		if (exec_it(cmd) != 0)
			exit(1);
		exit(0);
	}
	return (0);
}

/* Execute les commandes */
static int	go_exec(t_xek *x)
{
	int	i;
	int	ret;
	
	/* On lance un process pour chaque commande */
	i = 0;
	while (i < x->nb_cmd)
	{
		launch_process(&(x->cmd[i]), x);
		i++;
	}
	close_all(x);
	i = 0;
	while (i < x->nb_cmd)
	{
		waitpid(x->cmd[i].pid, &ret, WUNTRACED);
		if (WIFEXITED(ret))
		{
			x->cmd->data->code_err = WEXITSTATUS(ret);
		}
		else
		{

			x->cmd->data->code_err = WTERMSIG(ret) + 128;
			if (x->cmd->data->code_err == 139)
				printf("Segmentation Fault BOOM !\n");
			else
				printf("Interrupted with signal %d\n", x->cmd->data->code_err);
		}
		i++;
	}
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

	go_exec(data->x);

	destroy_exec(data->x);

	return (0);
}
