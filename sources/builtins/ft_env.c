/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:11:48 by tas               #+#    #+#             */
/*   Updated: 2023/04/23 01:09:32 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

t_list  **get_list_env(char **env)
{
    int i;
    t_list  **list_env;

    i = 0;
    list_env = malloc(sizeof(t_list));
    ft_memset(list_env, 0, sizeof(t_list));
    while (env[i] != NULL)
    {
        add_list(list_env, env[i]);
        i++;
    }
    return (list_env);
}

int ft_env()
{
    t_list  *tmp;

    tmp = *list_ENVI;
    while (*list_ENVI != NULL) {
        printf("%s\n", (*list_ENVI)->content);
        (*list_ENVI) = (*list_ENVI)->next;
    }
    *list_ENVI = tmp;
    return 0;
}

// int main(int argc, char **argv, char **env)
// {
//     (void)argc;
//     (void)argv;
//     list_ENVI = get_list_env(env);
//     ft_env();
// }