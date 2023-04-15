/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:07:07 by tas               #+#    #+#             */
/*   Updated: 2023/04/15 01:40:40 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* create child process */
int	child_process(t_data *data, char **__environ)
{
	data->pid = fork();
	if (data->pid < 0)
		return (1);
	if (data->pid == 0)
		execve(data->path_cmd, data->token_cmd, __environ);
	else
        waitpid(data->pid, NULL, 0);
	return (0);
}

int word_process(char *full_token, t_data *data, char **env, t_path path)
{
    init_param(data, full_token, env, path);
    child_process(data, env);
    return (0);
}

/*Exec simple sans operateurs pour l'instant*/
int simple_exec(t_list **list_token, char **env)
{
    t_data data;
    t_path  path;
    t_list  *tmp;
    char    *cmd_with_arg;
    
    tmp = *list_token;
    cmd_with_arg = "";
    ft_memset(&data, 0, sizeof(t_data));
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
    word_process(cmd_with_arg, &data, env, path);
    (*list_token) = tmp;
    return (0);
}

int creating_process(t_list **list_token, char **env)
{
	// if (check_pipes(list_token))
	// 	pipes_process();
	simple_exec(list_token, env);
	return (0);
}