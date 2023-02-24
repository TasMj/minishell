/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:15:52 by tmejri            #+#    #+#             */
/*   Updated: 2023/02/24 16:24:02 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Return 1 if the command line contain a quote, 0 if not */
int contain_a_quoate(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '|' || str[i] == '&' || str[i] == ';' || str[i] == '<'
            || str[i] == '>' || str[i] == '(' || str[i] == ')' || str[i] == '$'
            || str[i] == '`' || str[i] == 92 || str[i] == 34 || str[i] == 39
            || str[i] == 32 || str[i] == 9 || str[i] == 10)
                return (1);
        i++;
    }
    return (0);
}
