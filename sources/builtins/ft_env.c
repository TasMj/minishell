/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:11:48 by tas               #+#    #+#             */
/*   Updated: 2023/05/19 15:25:29 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

/*TO DO
-à ajouter direct comme ça dans le code et si pb faire un getinput et strncmp
*/
t_list  **get_list_env(char **env)
{
    int i;
    t_list  **list_env;

    i = 0;
    list_env = malloc(sizeof(t_list));
    ft_memset(list_env, 0, sizeof(t_list));
    while (env[i] != NULL)
    {
        add_list(list_env, env[i], 0);
        i++;
    }
    return (list_env);
}

int ft_env(t_list **list_cmd)
{
    t_list  *tmp;
    t_list  *tmp_cmd;

    tmp_cmd = *list_cmd;
    if ((*list_cmd)->next != NULL)
    {
        printf("env: ‘%s’: No such file or directory\n", (*list_cmd)->next->content);
        *list_cmd = tmp_cmd;
        return (1);
    }
    tmp = *list_ENVI;
    while (*list_ENVI != NULL) {
        printf("%s\n", (*list_ENVI)->content);
        (*list_ENVI) = (*list_ENVI)->next;
    }
    *list_ENVI = tmp;
    return 0;
}
