/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:56:12 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/04 21:30:11 by jthuysba         ###   ########.fr       */
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

int	check_access(char *file, t_cmd *cmd)
{
	if (access(file, F_OK) != -1)
	{
		if (access(file, R_OK | X_OK) != -1)
		{
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
		put_str_err("minishell: ");
		put_str_err(file);
		put_str_err(": No such file or directory\n");
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
		if (cmd->redir[i] == STDOUT)
			fd = open(cmd->file[i], O_CREAT | O_TRUNC | O_RDWR, 0666);
		else if (cmd->redir[i] == APPEND)
			fd = open(cmd->file[i], O_CREAT | O_APPEND | O_RDWR, 0666);
		else if (cmd->redir[i] == STDIN)
		{
			fd = open(cmd->file[i], O_RDONLY);
			if (fd < 0)
			{
				put_str_err("minishell: ");
				put_str_err(cmd->file[i]);
				put_str_err(": No such file or directory\n");
				if (!(x->nb_cmd > 1 && cmd->id == 0))
					cmd->data->code_err = 1;
				return (1);
			}
		}
		else if (cmd->redir[i] == HEREDOC)
		{
			fd = x->hdoc[x->hdoc_index].hd_pipe[0];
			x->hdoc_index++;
		}
		if (cmd->redir[i] != HEREDOC)
		{
			if (check_access(cmd->file[i], cmd) == 1)
			{
				cmd->data->code_err = 1;
				return (1);
			}
		}
		if (fd == -1)
			return (1);
		if (cmd->redir[i] == STDOUT || cmd->redir[i] == APPEND)
			dup2(fd, STDOUT_FILENO);
		else if (cmd->redir[i] == STDIN || cmd->redir[i] == HEREDOC)
			dup2(fd, STDIN_FILENO);
		close(fd);
		i++;
	}
	return (0);
}

int	exec_it(t_cmd *cmd, t_minishell *data)
{
	//Si commande invalide
	if (!cmd->path && is_builtin(cmd) == 0 && has_slash(cmd) == 0)
	{
		ft_exit(data);
	}
	cmd->tab_env = lst_to_tab(g_list_env);
	// signal_ignore();
	if (has_slash(cmd) == 1)
	{
		if (execve((*cmd->cmd)->content, cmd->tab, cmd->tab_env) != 0)
			return (1);//WIP
		exit (0);
	}
	else
	{
		if (execve(cmd->path, cmd->tab, cmd->tab_env) != 0)
			return (1);//WIP
		exit (0);
	}
	return (0);
}
