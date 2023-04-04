/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:55:26 by tas               #+#    #+#             */
/*   Updated: 2023/04/04 19:53:28 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int word_process(t_list *list_token, t_pipex *pipex, char **env, t_path path)
{
    if (is_executable(list_token->content) == 0)
        return (err_msg(2));
    else
    {
        
        // ft_memset(&pipex, 0, sizeof(t_pipex));
        init_param(pipex, list_token->content, env, path);
        child_process(pipex, env);
    }
    return (0);
}
