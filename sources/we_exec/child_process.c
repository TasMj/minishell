/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:56:12 by jthuysba          #+#    #+#             */
/*   Updated: 2023/06/06 18:54:00 by jthuysba         ###   ########.fr       */
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
		dup2(x->pipe[x->nb_cmd - 2][0], STDIN_FILENO);
	else
	{
		dup2(x->pipe[cmd->id - 1][0], STDIN_FILENO);
		dup2(x->pipe[cmd->id][1], STDOUT_FILENO);
	}
	close_all(x);
	return ;
}

int	grab_hdoc_pipe(t_xek *x)
{
	int	i;

	i = 0;
	while (i < x->hdoc_index)
		i++;
	x->hdoc_index++;
	return (x->hdoc[i].hd_pipe[0]);
}

/* On ouvre nos fichiers et on redirige selon le type en ecrasant la pipe */
int	open_n_dup(t_cmd *cmd, t_xek *x)
{
	(void) x;
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
		else if (cmd->redir[i] == HEREDOC)
			fd = grab_hdoc_pipe(x);
		if (fd == -1)
			exit(1);//WIP ERROR
		if (cmd->redir[i] == STDOUT || cmd->redir[i] == APPEND)
			dup2(fd, STDOUT_FILENO);
		else if (cmd->redir[i] == STDIN || cmd->redir[i] == HEREDOC)
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
		exit (0);
	}
	else
	{
		if (execve(cmd->path, cmd->tab, cmd->tab_env) != 0)
			return (1);
		exit (0);
	}
	return (0);
}
