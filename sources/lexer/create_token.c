/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:36:17 by tas               #+#    #+#             */
/*   Updated: 2023/03/13 00:23:54 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* read and stock input */
char    *get_input(void)
{
    char* input;

    input = readline("minishell$>");
    if (input == NULL) {
        printf("Erreur de lecture de la input.\n");
        exit(EXIT_FAILURE);
    }
	add_history(input);
    return input;
}

/* return 1 if space or new line */
int is_a_separator(char c)
{
    if (c == ' ' || (c >= 9 && c <= 13))
        return (1);
    return (0);
}

/* add to the list, word ready without space. take words with quotes */
void    add_list(t_list **list_token, char *stockage)
{
    t_list *to_add;
    
    to_add = ft_lstnew(stockage);
    // (*list_token) = ft_lstnew((*list_token), stockage);
    ft_lstadd_back(list_token, to_add);
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
    char *word_ready;

    i = 0;
    start = 0;
    end = 0;
    flag = 0;
    while(i < ft_strlen(input))
    {
        if (is_a_separator(input[i]) == 1)
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
                while (!(is_a_separator(input[i])))
                    i++;
            end = i;
            // end = i + 1;
            if (flag == 1)
                i++;
            stockage = ft_strdup_size(input + start, (end - start));
            word_ready = ft_strdup_size(stockage, ft_strlen(stockage));
            add_list(list_token, word_ready);
            free(stockage);
        }
    }
    return (list_token);
}
