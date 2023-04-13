/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:07:07 by tas               #+#    #+#             */
/*   Updated: 2023/04/13 17:40:48 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* create child process */
int	child_process(t_pipex *pipex, char **__environ)
{
	pipex->pid = fork();
	if (pipex->pid < 0)
		return (1);
	if (pipex->pid == 0)
		execve(pipex->path_cmd, pipex->token_cmd, __environ);
	else
        waitpid(pipex->pid, NULL, 0);
	return (0);
}

int word_process(char *full_token, t_pipex *pipex, char **env, t_path path)
{
    init_param(pipex, full_token, env, path);
    child_process(pipex, env);
    return (0);
}

//Exec simple sans operateurs pour l'instant
int simple_exec(t_list **list_token, char **env)
{
    t_pipex pipex;
    t_path  path;
    t_list  *tmp;
    char    *cmd_with_arg;
    
    tmp = *list_token;
    cmd_with_arg = "";
    ft_memset(&pipex, 0, sizeof(t_pipex));
    while ((*list_token) != NULL && (*list_token)->type == 0)
    {
        cmd_with_arg = ft_strjoin(cmd_with_arg, (*list_token)->content);
        if ((*list_token)->next != NULL)
        {
            cmd_with_arg = ft_strjoin(cmd_with_arg, " ");
            (*list_token) = (*list_token)->next;
        }
        else
            break;
    }
    word_process(cmd_with_arg, &pipex, env, path);
    (*list_token) = tmp;
    return (0);
}

int creating_process(t_list **list_token, char **env)
{
	if (check_pipes(list_token) == 1)
		pipe_exec(list_token, env);
	// simple_exec(list_token, env);
	return (0);
}