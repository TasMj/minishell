/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:07:07 by tas               #+#    #+#             */
/*   Updated: 2023/04/04 19:53:24 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 1) check si la première commande est une commande executable 
// 2) si oui créer un nv processus fils en utilisant la fonction fork

/* check if it's executable */
int is_executable(char *token)
{
    char    *env_path;
    char    **path;
    char    *full_path;
    struct  stat buffer;
    int     is_executable;
    int     i;
    
    if ((!token) || token[0] == '\0')
        return (2);
    env_path = getenv("PATH");
    path = ft_split(env_path, ':');
    i = 0;    
    while (path[i])
    {
        full_path = ft_strjoin_mod(path[i], "/", 0);
        full_path = ft_strjoin_mod(full_path, token, 1);
        is_executable = !access(full_path, X_OK);
        if (stat(full_path, &buffer) == 0 && is_executable)
            return (1);
        i++;
    }
    return (0);
}

/* if the command is executable, create a child process. If not exit */
int creating_child_process(t_list **list_token, char ** env)
{
    t_pipex pipex;
    t_path  path;
    t_list  *tmp;
    
    tmp = *list_token;    
    while ((*list_token) != NULL)
    {
        if ((*list_token)->type == WORD)
            word_process((*list_token), &pipex, env, path);
        // else if ((*list_token)->type == APPEND)
            
        // else if ((*list_token)->type == HEREDOC)
            
        // else if ((*list_token)->type == STDIN)
            
        // else if ((*list_token)->type == STDOUT)
            
        // else if ((*list_token)->type == PIPE)
            
        (*list_token) = (*list_token)->next;
    }
    (*list_token) = tmp;
    return (0);
}


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

int	extract_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}
