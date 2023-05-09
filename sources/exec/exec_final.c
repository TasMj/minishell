/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_final.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:01:28 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/09 18:11:07 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Retourne le nombre de commandes
int	nb_cmd(t_list *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type != WORD)
			count++;
		token = token->next;
	}
	count++;
	return (count);
}

//Retourne le nombre de token avant l'operateur
int	cmd_size(t_list *token)
{
	int	count;
	
	count = 0;
	while (token && token->type == WORD)
	{
		count++;
		token = token->next;
	}
	return (count);
}

// Retourne la commande avec les args jusquau premier operateur
char	**get_cmd(t_list *token)
{
	char		**cmd;
	int		i;

	cmd = malloc(sizeof(char *) * (cmd_size(token) + 1));
	i = 0;
	while (token && token->type == WORD)
	{
		cmd[i] = ft_strdup_size(token->content, ft_strlen(token->content));
		i++;
		token = token->next;
	}
	cmd[i] = 0;
	return (cmd);
}

// Compte les pipes dans les token
int	count_pipes(t_list *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == PIPE)
			count++;
		token = token->next;
	}
	return (count);
}

// Setup fd in et out pour chaque commande
void	set_fd(t_cmd *cmd, t_exec *data)
{
	if (cmd->id == 0)
	{
		cmd->fd_in = STDIN_FILENO;
		cmd->fd_out = data->fd[0][1];	
	}
	else if (cmd->id == data->nb_pipes)
	{
		cmd->fd_in = data->fd[cmd->id - 1][0];
		cmd->fd_out = STDOUT_FILENO;
	}
	else
	{
		cmd->fd_in = data->fd[cmd->id - 1][0];
		cmd->fd_out = data->fd[cmd->id][1];
	}
}

// Setup chaque commande dans une struct cmd
void	setup_cmd(t_exec *data)
{
	int	i;
	t_list	*token;
	t_path	p;

	token = *(data->token);
	data->cmd = malloc(sizeof(t_cmd) * nb_cmd(token));
	i = 0;
	while (token)
	{
		data->cmd[i].id = i;
		data->cmd[i].cmd = get_cmd(token);
		data->cmd[i].path = find_path(data->env, data->cmd[i].cmd[0], p);
		set_fd(&(data->cmd[i]), data);
		while (token->type == WORD && token->next)
			token = token->next;
		token = token->next;
		i++;
	}
}

// Ferme toutes les pipes jusqu'a la pipe end
void	close_all(t_exec *data, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		close(data->fd[i][0]);
		close(data->fd[i][1]);
		i++;
	}
}

// Setup les pipes
void	setup_pipes(t_exec *data)
{
	int	i;

	data->nb_pipes = count_pipes(*(data->token));
	i = 0;
	data->fd = malloc(sizeof(int *) * data->nb_pipes);
	while (i < data->nb_pipes)
	{
		data->fd[i] = malloc(sizeof(int) * 2);
		if (pipe(data->fd[i]) < 0)
		{
			close_all(data, i);
			return ;
		}
		i++;
	}
}

int	exec_cmd(t_cmd *cmd, t_exec *data)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		printf("\ncmd = %s\nin = %d\nout = %d\nid = %d\n\n", cmd->cmd[0], cmd->fd_in, cmd->fd_out, cmd->id);
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		// close_all(data, data->nb_pipes - 1);
		execve(cmd->path, cmd->cmd, data->env);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

int	exec(t_exec *data)
{
	int	i;

	while (i < nb_cmd(*(data->token)))
	{
		if (exec_cmd(&(data->cmd[i]), data) != 0)
			return (1);
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
	if (exec(&data))
		return (1);
	close_all(&data, data.nb_pipes - 1);
	return (0);
}