/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:58:32 by tas               #+#    #+#             */
/*   Updated: 2023/05/19 17:49:33 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* return 1 if space or new line */
int is_a_space(char c)
{
    if (c == ' ' || (c >= 9 && c <= 13))
        return (1);
    return (0);
}

/* return 1 if space, <, <<, >, >>, | or new line */
int is_a_separator(char c)
{
    if (is_a_space(c) == 1 || c == '|' || c == '>' || c == '<' || c == '\0')
        return (1);
    return (0);
}

/* delet all the empty token */
int del_empty_token(t_list **list_token)
{
    t_list  *tmp;

    tmp = *list_token;
    while (*list_token && (*list_token)->next->next)
    {
        if (ft_strlen((*list_token)->next->content) == 0)
            (*list_token)->next = (*list_token)->next->next;
        else
            (*list_token) = (*list_token)->next;
    }
    *list_token = tmp;
    return (0);
}
