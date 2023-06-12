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
#include "heredoc.h"

/* On lance un process pour chaque commande */
int	launch_process(t_cmd *cmd, t_xek *x)
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
int	go_exec(t_xek *x)
{
	int	i;
	
	/* On lance un process pour chaque commande */
	i = 0;
	while (i< x->nb_cmd)
	{
		launch_process(&(x->cmd[i]), x);
		i++;
	}
	close_all(x);
	i = 0;
	while (i < x->nb_cmd)
	{
		waitpid(x->cmd[i].pid, NULL, 0);
		i++;
	}
	return (0);
}

/* Execute les tokens
-> cat < file | wc -l > file2 */
int	we_exec(t_minishell *data)
{
	data->x = malloc(sizeof(t_xek));
	ft_memset(data->x, 0, sizeof(t_xek));

	prep_cmd(data);

	open_pipes(data);

	exec_heredoc(data);

	go_exec(data->x);

	destroy_exec(data->x);

	return (0);
}
