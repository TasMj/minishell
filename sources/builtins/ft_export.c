/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:11:23 by tas               #+#    #+#             */
/*   Updated: 2023/05/16 17:40:36 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

t_list	**list_ENVI;

/*TO DO
- export simple return la list par ordre aasci
- export a ---> a='' mais e s'affiche qu'avec export
- si export une var qui existe déja ça la modifie
//MODIFIER LA VAR SI ELLE EXISTE
*/

int check_equal(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

char    *take_off_equal(char *str)
{
    int     i;
    char    *var;
    
    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    var = ft_strdup_size(str, i);
    return (var);
}

int is_in_env(char *str)
{
    t_list  *tmp;

    tmp = *list_ENVI;
    while (*list_ENVI)
    {
        if (ft_strcmp(str, take_off_equal((*list_ENVI)->content)) == 0)
            return (1);
        (*list_ENVI) = (*list_ENVI)->next;
    }
    *list_ENVI = tmp;
    return (0);
}

/* swap 2 elts d'une liste */
// void	ft_swap(t_list *first, t_list *second)
// {
//     t_list  *tmp;

//     tmp = first;
//     first = second;
//     second = tmp;
// }

// t_list  **ft_copy_list(t_list  **copy)
// {
//     while (*list_ENVI)
//     {
//         add_list(copy, (*list_ENVI)->content);
//         (*list_ENVI) = (*list_ENVI)->next;
//     }
//     return (copy);
// }

// int is_sorted(t_list **list)
// {
//     while ((*list)->next != NULL)
//     {
//         if (ft_strncmp((*list)->content, (*list)->next->content, ft_strlen((*list)->content)) > 0)
//             return (1);
//         (*list) = (*list)->next;
//     }
//     return (0);    
// }

// int sort_env(t_list **list)
// {
//     t_list  *tmp;
    
//     tmp = *list;
//     while (is_sorted(list) == 1)
//     {
//         *list = tmp;
//         if (ft_strncmp((*list)->content, (*list)->next->content, ft_strlen((*list)->content)) > 0)
//             ft_swap
//     }
// }

// int sort_env_ascii(void)
// {
//     t_list  **copy;

//     copy = malloc(sizeof(t_list));
//     ft_memset(copy, 0, sizeof(t_list));
//     copy = ft_copy_list(copy);
//     print_list(copy);
//     return (0);
// }

int ft_export(t_list **list_token)
{
    t_list  *tmp;
    
    tmp = *list_ENVI;
    if (ft_lstsize(*list_token)== 1)
    {
        printf("en cours de construction\n");
        // sort_env_ascii();
    }
    else
    {
        while (*list_token != NULL)
        {
            (*list_token) = (*list_token)->next;
            if (check_equal((*list_token)->content) == 1)
            {
                if (is_in_env(take_off_equal((*list_token)->content)) == 0)
                    add_list(list_ENVI, (*list_token)->content);
                else
                {
                    while (*list_ENVI)
                    {
                        if (ft_strcmp(take_off_equal((*list_ENVI)->content), take_off_equal((*list_token)->content)) == 1)
                            (*list_ENVI) = (*list_ENVI)->next;
                        else if (ft_strcmp(take_off_equal((*list_ENVI)->content), take_off_equal((*list_token)->content)) == 0)
                        {
                            (*list_ENVI)->content = ft_strjoin_mod("", (*list_token)->content, 0);
                            break;
                        }
                    }
                }
            }
            (*list_token) = (*list_token)->next;
        }        
    }
    *list_ENVI = tmp;
    return (0);
}

