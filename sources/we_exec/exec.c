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

/* Redirige l'entree et/ou la sortie d'une commande vers une pipe */
void	dup_pipe(t_cmd *cmd, t_xek *x)
{
	if (x->nb_cmd == 1)
		return ;
	if (cmd->id == 0)
		dup2(x->pipe[0][1], STDOUT_FILENO);
	else if (cmd->id == x->nb_cmd - 1)
	{
		dup2(x->pipe[x->nb_cmd - 2][0], STDIN_FILENO);
	}
	else
	{
		dup2(x->pipe[cmd->id - 1][0], STDIN_FILENO);
		dup2(x->pipe[cmd->id][1], STDOUT_FILENO);
	}
	close_all(x);
	return ;
}

/* On ouvre nos fichiers et on redirige selon le type en ecrasant la pipe */
int	open_n_dup(t_cmd *cmd)
{
	int	i;
	int	fd;

	if (cmd->nb_redir == 0)
		return (0);
	i = 0;
	while (cmd->file[i])
	{
		/* Selon le type de redir on ouvre le file differement */
		if (cmd->redir[i] == STDOUT)
			fd = open(cmd->file[i], O_CREAT | O_TRUNC | O_RDWR, 0666);
		else if (cmd->redir[i] == APPEND)
			fd = open(cmd->file[i], O_CREAT | O_APPEND | O_RDWR, 0666);
		else if (cmd->redir[i] == STDIN)
			fd = open(cmd->file[i], O_RDONLY);
		//WIP HEREDOC
		if (fd == -1)
			exit(1);//WIP ERROR
		if (cmd->redir[i] == STDOUT || cmd->redir[i] == APPEND)
			dup2(fd, STDOUT_FILENO);
		else if (cmd->redir[i] == STDIN) //WIP HEREDOC
			dup2(fd, STDIN_FILENO);
		close(fd);
		i++;
	}
	return (1);
}

int	exec_it(t_cmd *cmd)
{
	cmd->tab_env = lst_to_tab(g_list_env);
	if (has_slash(cmd) == 1)
	{
		if (execve((*cmd->cmd)->content, cmd->tab, cmd->tab_env) != 0)
			return (1);
		printf("executed !");
		exit (0);
	}
	else
	{
		if (execve(cmd->path, cmd->tab, cmd->tab_env) != 0)
			return (1);
		printf("executed !");
		exit (0);
	}
	return (0);
}

/* On lance un process pour chaque commande */
int	launch_process(t_cmd *cmd, t_xek *x)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (1);
	if (cmd->pid == 0)
	{
		dup_pipe(cmd, x);
		open_n_dup(cmd);
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

	prep_cmd(data);
	open_pipes(data);
	go_exec(data->x);

	destroy_all(data->x);
	return (0);
}
