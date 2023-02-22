/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:50:57 by tmejri            #+#    #+#             */
/*   Updated: 2023/02/22 17:38:44 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *get_input()
{
    char* input;

    input = readline("$");
    if (input == NULL) {
        printf("Erreur de lecture de la input.\n");
        exit(EXIT_FAILURE);
    }
	add_history(input);

    printf("Input: %s\n\n", input);
    return input;
}

char    **get_token(char *input)
{
    char    **tab_token;

    tab_token = all_split(input, ' ', 34);
    return (tab_token);
}


int main(void) 
{
    char *input;
    char **tab_token;
    
	input = get_input();
    tab_token = get_token(input);
    int i = 0;
    while (tab_token[i])
    {
        printf("[%d] %s\n", i, tab_token[i]);
        i++;
    }
    free(input);
    return 0;
}

int main()
{
    t_list **list_token;
	int		size_list;
    char *input;

	list_token = malloc(sizeof(t_list));
	if (!list_token)
	{
		free_list(list_token);
		return (1);
	}
	list_token[0] = NULL;
    while (get_input())
	{
		input = get_input();
    // tab_token = get_token(input);
    // int i = 0;
    // while (tab_token[i])
    // {
    //     printf("[%d] %s\n", i, tab_token[i]);
    //     i++;
    // }
	}
    free(input);
    return (0);
}