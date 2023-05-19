/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:09:31 by tas               #+#    #+#             */
/*   Updated: 2023/05/20 00:04:03 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

int ft_n(char *str)
{
    int i;

    i = 0;
    if (str[i] && str[i + 1] && str[i] == '-' && str[i+1] == 'n')
    {
        i += 2;
        while (str[i])
        {
            if (str[i] != 'n')
                return (1);
            i++;
        }
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
    		while (ft_strncmp((*list_token)->content, "-n", 2) == 0 && ft_n((*list_token)->content) == 0)
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
