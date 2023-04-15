/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:36:17 by tas               #+#    #+#             */
/*   Updated: 2023/04/15 01:52:27 by tas              ###   ########.fr       */
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

/* découpe le mot en fonction de si il s'agit d'un mot simple ou entre quote (single ou double)*/
t_list    **create_token(t_list **list_token, char *input)
{
    int i;
    int start;
    int end;
    int flag;
    char quote;
    char *stockage;

    i = 0;
    start = 0;
    end = 0;
    flag = 0;
    while(i < ft_strlen(input))
    {
        if (is_a_space(input[i]) == 1)
            i++;
        else
        {
            start = i;
            if (input[i] == 39 || input[i] == 34)
            {
                quote = input[i];
                flag = 1;
                i++;
                while (input[i] != quote && flag == 1)
                    i++;
                i++;
            }
            else
            {
                if (input[i] == '|' || input[i] == '>' || input[i] == '<')
                {
                    i++;
                    if (input[i] == '>' || input[i] == '<')
                        i++;
                }
                else
                {
                    while (is_a_separator(input[i]) == 0)
                        i++;
                }
            }
            end = i;
            if (flag == 1)
                i++;
            stockage = ft_strdup_size(input + start, (end - start));
            add_list(list_token, stockage);
            // free(stockage);
        }
    }
    return (list_token);
}
