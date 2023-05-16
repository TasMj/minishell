/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:09:31 by tas               #+#    #+#             */
/*   Updated: 2023/05/16 17:40:01 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

/* TO DO
- tester echo sdjfqldhfqs<lfhj
- echo t"t" --> t t au lieu de tt
*/

int    to_display(t_list **list_token, t_echo *e)
{
    (*list_token) = (*list_token)->next;
	if (ft_strncmp((*list_token)->content, "-n", 2) == 0)
    {
        e->flag = 1;
        if ((*list_token)->next == NULL)
            return (0);
        (*list_token) = (*list_token)->next;
    }
    while (*list_token)
    {
        e->to_free = 1;
        e->stockage = ft_strjoin(e->stockage, (*list_token)->content);
        if ((*list_token)->next != NULL)
            e->stockage = ft_strjoin(e->stockage, " ");
        (*list_token) = (*list_token)->next;
    }
    return (0);
}

// int ft_echo(t_list **list_token)
// {
    // t_echo  *e;
// 
    // e = malloc(sizeof(t_echo));
    // ft_memset(e, 0, sizeof(t_echo));
    // e->flag = 0;
    // e->to_free = 0;
    // e->stockage = NULL;
    // e->stockage = "";
    // e->tmp = *list_token;
    // while ((*list_token) != NULL)
    // {
		// if (ft_strncmp((*list_token)->content, "echo", 4) == 0 && (*list_token)->next != NULL)
            // to_display(list_token, e);
        // else
            // (*list_token) = (*list_token)->next;
    // }
    // if (e->flag != 1)
        // printf("%s\n", e->stockage);
    // else
        // printf("%s", e->stockage);
    // if (e->to_free == 1)
        // free(e->stockage);
    // *list_token = e->tmp;
    // return (0);
// }


/*LE BON*/
int ft_echo(t_list **list_token)
{
    t_list  *tmp;
    char    *stockage;
    int     flag;
    int     to_free;

    flag = 0;
    to_free = 0;
    stockage = NULL;
    stockage = "";
    tmp = *list_token;
    while ((*list_token) != NULL)
    {
		if (ft_strncmp((*list_token)->content, "echo", 4) == 0 && (*list_token)->next != NULL)
        {
            (*list_token) = (*list_token)->next;
    		if (ft_strncmp((*list_token)->content, "-n", 2) == 0)
            {
                flag = 1;
                if ((*list_token)->next == NULL)
                    break;
                (*list_token) = (*list_token)->next;
            }
            while (*list_token)
            {
                to_free = 1;
                stockage = ft_strjoin(stockage, (*list_token)->content);
                if ((*list_token)->next != NULL)
                    stockage = ft_strjoin(stockage, " ");
                (*list_token) = (*list_token)->next;
            }
        }
        else
            (*list_token) = (*list_token)->next;
    }
    if (flag != 1)
        printf("%s\n", stockage);
    else
        printf("%s", stockage);
    if (to_free == 1)
        free(stockage);
    *list_token = tmp;
    return (0);
}
