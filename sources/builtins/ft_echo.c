/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:09:31 by tas               #+#    #+#             */
/*   Updated: 2023/05/25 12:57:32 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

/* TO DO
- -n-n-n
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
    		if (ft_strlen((*list_token)->content) == 2 && ft_strncmp((*list_token)->content, "-n", 2) == 0)
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
                if ((*list_token)->next != NULL && (*list_token)->next->flag_space == 1) 
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
