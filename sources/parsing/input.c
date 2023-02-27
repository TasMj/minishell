/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:50:57 by tmejri            #+#    #+#             */
/*   Updated: 2023/02/27 11:25:37 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *get_input(void)
{
    char* input;

    input = readline("$");
    if (input == NULL) {
        printf("Erreur de lecture de la input.\n");
        exit(EXIT_FAILURE);
    }
	add_history(input);
    // printf("Input: %s\n\n", input);
    return input;
}
