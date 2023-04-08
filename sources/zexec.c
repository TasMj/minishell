/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zexec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:08:59 by tas               #+#    #+#             */
/*   Updated: 2023/04/08 12:09:03 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
