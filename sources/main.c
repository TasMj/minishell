/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:39:21 by tas               #+#    #+#             */
/*   Updated: 2023/03/01 15:18:34 by tas              ###   ########.fr       */
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

    input = get_input();
    if (check_args(input) == 1)
        return (err_msg(1));

    list_token = malloc(sizeof(t_list));
	list_token[0] = NULL;
    create_token(list_token, input);
    // print_list(list_token);
    
    
    return (0);
}


// int main()
// {
    // t_list **list_token;
	// int		size_list;
    // char *input;
// 
	// list_token = malloc(sizeof(t_list));
	// if (!list_token)
	// {
		// free_list(list_token);
		// return (1);
	// }
	// list_token[0] = NULL;
    // while (get_input())
	// {
		// input = get_input();
	// }
    // free(input);
    // return (0);
// }