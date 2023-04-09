/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:39:21 by tas               #+#    #+#             */
/*   Updated: 2023/04/09 12:45:29 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    init_list(t_list **list_token, char *input)
{
    list_token = create_token(list_token, input);
    substitute_dollar(list_token);
    get_type(list_token);
    remove_list_quotes(list_token);
}


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
        if (check_pair_quote(input) == 1)
            err_msg(1);
        else
        {
            list_token = malloc(sizeof(t_list));
	        list_token[0] = NULL;
            init_list(list_token, input);
            // print_list(list_token);
            creating_child_process(list_token, env);
        }
        
    }
    return (0);
}
