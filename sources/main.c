/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:39:21 by tas               #+#    #+#             */
/*   Updated: 2023/03/14 19:10:05 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    (void)env;
    char *input;
    t_list **list_token;

    while(1)
    {
        input = get_input();
        // if (check_pair_quote(input) == 1)
            // err_msg(1);
        // else
        // {
            list_token = malloc(sizeof(t_list));
	        list_token[0] = NULL;
            list_token = create_token(list_token, input);
            substitute_dollar(list_token);
        // }
    }
    
    // print_list(list_token);
    //free liste
    
    return (0);
}
