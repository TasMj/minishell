/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:15:52 by tmejri            #+#    #+#             */
/*   Updated: 2023/03/08 14:59:47 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Return 1 if the command line contain a quote, 0 if not */
int is_a_quoting(char c)
{
    if (c == '|' || c == '&' || c == ';' || c == '<' || c == '>' || c == '('
        || c == ')' || c == '$' || c == '`')
            return (1);
    return (0);
}

/*PB CAR NE LIS PAS LES QUOTES*/
/* check si après la première simple quote (') on trouve la deuxième
return 0 si pas de ', 1 si un seul ', 2 si on trouve la deuxième */
int check_pair_single_quote(char *str)
{
    int i;
    int flag;

    i = 0;    
    flag = 0;
    while (str[i])
    {
        if (str[i] == 39)
        {
            flag = 1;
            while(str[i])
            {
                i++;
                if (str[i] == 39 && flag == 1)
                    return(2);
            }
            return (1);
        }
        i++;
    }
    return (0);
}

/* check si après la première simple quote (") on trouve la deuxième
return 0 si pas de ", 1 si un seul ", 2 si on trouve la deuxième */
int check_pair_double_quote(char *str)
{
    int i;
    int flag;

    i = 0;
    flag = 0;
    while (str[i])
    {
        if (str[i] == 34)
        {
            flag = 1;
            while(str[i])
            {
                i++;
                if (str[i] == 34 && flag == 1)
                    return(2);
            }
            return (1);
        }
        i++;
    }
    return (0);
}

/* découpe le mot comme il faut pour les mots entre quote (conserve les espaces) */
char *word_quote(char *stockage, int quote)
{
    int i;
    int start;
    int flag;
    char *new;

    i = 0;
    flag = 0;
    start = 0;
    new = NULL;
    while (stockage[i] && flag < 2)
    {
        while (is_a_separator(stockage[i]) == 1 || stockage[i] == quote)
        {
            if (stockage[i] == quote)
                flag++;
            i++;
        }
        start = i - 1;
        while (stockage[i] != quote)
            i++;
        if(stockage[i] == quote)
            flag++;
    }
    new = ft_strdup_size(stockage + start, ((i + 1) - start));
    // new = ft_strdup_size(stockage + start, (i - start)); et start = i et pas i - 1
    return (new);
}
