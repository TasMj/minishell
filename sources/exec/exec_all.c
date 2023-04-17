/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:12:39 by jthuysba          #+#    #+#             */
/*   Updated: 2023/04/17 17:26:14 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Retourne le token avant elem
t_list	*lst_previous(t_list *token, t_list *elem)
{
	if (!token->next)
		return (NULL);
	while (token->next != elem && token)
		token = token->next;
	return (token);
}

//Retourne le nombre de token avant l'operateur
int	cmd_size(t_list *token)
{
	int	count;
	
	count = 0;
	while (token && token->type == 0)
	{
		count++;
		token = token->next;
	}
	return (count);
}

//Retourne la commande avec les args jusquau premier operateur
char	**get_cmd(t_list *token)
{
	char		**cmd;
	int		i;

	cmd = malloc(sizeof(char *) * (cmd_size(token) + 1));
	i = 0;
	while (token && token->type == 0)
	{
		cmd[i] = ft_strdup_size(token->content, ft_strlen(token->content));
		i++;
		token = token->next;
	}
	cmd[i] = 0;
	return (cmd);
}

//Execute la commande jusquau premier operateur
int	exec_mid(t_list *elem, char **env, t_exec ex)
{
	char		**cmd;
	pid_t		pid;
	t_path	p;
	(void) ex;

	cmd = get_cmd(elem);
	pid = fork();
	if (pid == 0)
	{
		// dup2(STDIN_FILENO, ex.fd[0]);
		// dup2(ex.fd[1], STDOUT_FILENO);
		// close(ex.fd[0]);
		// close(ex.fd[1]);
		execve(find_path(env, cmd[0], p), cmd, env);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

int	exec_first(t_list *elem, char **env, t_exec ex)
{
	char		**cmd;
	pid_t		pid;
	t_path	p;
	(void) ex;

	cmd = get_cmd(elem);
	pid = fork();
	if (pid == 0)
	{
		// dup2(ex.fd[1], STDOUT_FILENO);
		// close(ex.fd[0]);
		// close(ex.fd[1]);
		execve(find_path(env, cmd[0], p), cmd, env);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

int	exec_last(t_list *elem, char **env, t_exec ex)
{
	char		**cmd;
	pid_t		pid;
	t_path	p;
	(void) ex;

	cmd = get_cmd(elem);
	pid = fork();
	if (pid == 0)
	{
		// dup2(STDIN_FILENO, ex.fd[0]);
		// close(ex.fd[1]);
		// close(ex.fd[0]);
		execve(find_path(env, cmd[0], p), cmd, env);
	}
	waitpid(pid, NULL, 0);
	return (0);
}

int	last_cmd(t_list *token)
{
	while (token)
	{
		if (token->type != 0)
			return (0);
		token = token->next;
	}
	return (1);
}

void	rec_exec(t_list *token, t_list *elem, t_exec ex, char **env)
{
	(void) env;
	
	while (elem != token && elem->type == 0)
	{
		// printf("%s\n", elem->content);
		elem = lst_previous(token, elem);
	}
	// printf("%s\n\n", elem->content);
	if (elem != token)
		rec_exec(token, lst_previous(token, elem), ex, env);
	if (elem == token)							//Premiere commande
		exec_first(elem, env, ex);
	else if (last_cmd(elem->next) == 1)	//Derniere commande
		exec_last(elem->next, env, ex);
	else
		exec_mid(elem->next, env, ex);
}

int   exec_all(t_list *token, char **env)
{
	(void) env;
	t_exec	ex;
	
	pipe(ex.fd);
	rec_exec(token, ft_lstlast(token), ex, env);
	return (0);
}