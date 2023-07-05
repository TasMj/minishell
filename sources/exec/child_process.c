/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:56:12 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/05 15:35:01 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	check_access(char *file, t_cmd *cmd)
{
	if (access(file, F_OK) != -1)
	{
		if (access(file, R_OK) == -1)
		{
			cmd->data->code_err = 1;
			put_str_err("minishell: ");
			put_str_err((*cmd->cmd)->content);
			put_str_err(": ");
			put_str_err(file);
			put_str_err(": Permission denied\n");
			return (1);
		}
		else
			return (0);
	}
	else
	{
		cmd->data->code_err = 1;
		put_str_err("minishell: ");
		put_str_err(file);
		put_str_err(": No such file or directory\n");
		return (1);
	}
	return (0);
}

void	dup_fd(int fd, int redir)
{
	if (redir == STDOUT || redir == APPEND)
		dup2(fd, STDOUT_FILENO);
	else if (redir == STDIN || redir == HEREDOC)
		dup2(fd, STDIN_FILENO);
	close(fd);
}

int	open_type(int redir, char *file, t_xek *x)
{
	if (redir == STDOUT)
		return (open(file, O_CREAT | O_TRUNC | O_RDWR, 0666));
	else if (redir == APPEND)
		return (open(file, O_CREAT | O_APPEND | O_RDWR, 0666));
	else if (redir == STDIN)
		return (open(file, O_RDONLY));
	else if (redir == HEREDOC)
	{
		x->hdoc_index++;
		return (x->hdoc[x->hdoc_index - 1].hd_pipe[0]);
	}
	return (0);
}

/* On ouvre nos fichiers et on redirige selon le type en ecrasant la pipe */
int	open_n_dup(t_cmd *cmd, t_xek *x)
{
	int	i;
	int	fd;

	if (cmd->nb_redir == 0)
		return (0);
	i = 0;
	while (cmd->file[i])
	{
		fd = open_type(cmd->redir[i], cmd->file[i], x);
		if (cmd->redir[i] != HEREDOC)
			if (check_access(cmd->file[i], cmd) == 1)
				return (1);
		if (fd == -1)
			return (1);
		dup_fd(fd, cmd->redir[i]);
		i++;
	}
	return (0);
}
