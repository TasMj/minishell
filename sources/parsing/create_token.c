/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:36:17 by tas               #+#    #+#             */
/*   Updated: 2023/05/09 14:00:59 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* read and stock input */
char    *get_input(void)
{
    char* input;

    input = readline("\033[1;33mminishell$>\033[0m");
    if (input == NULL) {
        printf("Erreur de lecture de la input.\n");
        exit(EXIT_FAILURE);
    }
	add_history(input);
    return input;
}

void    delimit_token(t_substitution *s, char *input)
{
    if (input[s->i] == 39 || input[s->i] == 34)
    {
        // while (input[s->i] && input[s->i] != 39 && input[s->i] != 34)
            // s->i++;
        s->quote = input[s->i];
        s->flag = 1;
        s->i++;
        while (input[s->i] != s->quote && s->flag == 1)
            s->i++;
        s->flag = 0;
        s->i++;
        // printf("LA QUOTE: %c\n", input[s->i]);
    }
    else
    {
        if (input[s->i] == '|' || input[s->i] == '>' || input[s->i] == '<')
        {
            s->i++;
            if (input[s->i] == '>' || input[s->i] == '<')
                s->i++;
        }
        else if (is_a_separator(input[s->i]) == 0)
        {
            printf("ok\n");
            while (input[s->i] != 39 && input[s->i] != 34)
                s->i++;
        }
        else
        {
            while (is_a_separator(input[s->i]) == 0)
                s->i++;
        }
    }
}

/* découpe le mot en fonction de si il s'agit d'un mot simple ou entre quote (single ou double)*/
t_list  **create_token(t_list **list_token, char *input)
{
    t_substitution  *s;

    s = malloc(sizeof(t_substitution));
    ft_memset(s, 0, sizeof(t_substitution));
    s->i = 0;
    s->start = 0;
    s->end = 0;
    s->flag = 0;
    while(s->i < ft_strlen(input))
    {
        if (is_a_space(input[s->i]) == 1)
            s->i++;
        else
        {
            s->start = s->i;
            delimit_token(s, input);
            s->end = s->i;
            if (s->flag == 1)
                s->i++;
            s->stockage = ft_strdup_size(input + s->start, (s->end - s->start));
            add_list(list_token, s->stockage);
            // free(stockage);
        }
    }
    return (list_token);
}
