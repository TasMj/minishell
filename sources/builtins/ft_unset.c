/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:11:35 by tas               #+#    #+#             */
/*   Updated: 2023/04/23 01:06:11 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

char    *var_name(char *str)
{
    char    *stockage;
    int     i;

    i = 0;
    while (str[i] != '=')
        i++;
    stockage = ft_strdup_size(str, i);
    return (stockage);
}

int check_var(char *str)
{
    t_list  *tmp;

    tmp = *list_ENVI;
    while (*list_ENVI)
    {
        if (ft_strcmp(var_name((*list_ENVI)->content), str) == 0)
        {
            *list_ENVI = tmp;
            return (1);
        }
        (*list_ENVI) = (*list_ENVI)->next;
    }
    *list_ENVI = tmp;
    
    return (0);
}

void    del(char *str)
{
    t_list  *tmp_first;
    t_list  *tmp_next;

    tmp_first = *list_ENVI;
    if (ft_strcmp(var_name((*list_ENVI)->content), str) == 0)
    {
        (*list_ENVI) = (*list_ENVI)->next;
        tmp_first = *list_ENVI;
    }
    else
    {
        while((*list_ENVI)->next != NULL && ft_strcmp(var_name((*list_ENVI)->next->content), str) == 1)
                (*list_ENVI) = (*list_ENVI)->next;
        tmp_next = (*list_ENVI)->next->next;
        (*list_ENVI)->next = tmp_next;
    }
    *list_ENVI = tmp_first;
}

int ft_unset()
{
    t_list  **list_cmd;
    t_list  *tmp;
    
    list_cmd = malloc(sizeof(t_list));
    list_cmd[0] = NULL;
    list_cmd = get_list_input(list_cmd);
    tmp = *list_cmd;
    if (ft_strncmp((*list_cmd)->content, "unset", 5) == 1)
        return (1);
    else
    {
        (*list_cmd) = (*list_cmd)->next;
        while (*list_cmd != NULL)
        {
            if (check_var((*list_cmd)->content) == 1)
                del((*list_cmd)->content);
            (*list_cmd) = (*list_cmd)->next;
        }        
    }
    *list_cmd = tmp;
    return (0);
}

// int main(int argc, char **argv, char **__environ)
// {
//     (void)argc;
//     (void)argv;
//     (void)__environ;
//     list_ENVI = get_list_env(__environ);
//     while(1)
//     {
//         ft_unset();
//         print_list(list_ENVI);
//     }
// }
