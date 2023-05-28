/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:39:21 by tas               #+#    #+#             */
/*   Updated: 2023/05/28 13:46:10 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

int    init_list(t_list **list_token, char *input)
{
    list_token = create_token(list_token, input);
    substitute_dollar(list_token);
    get_type(list_token);
    if (err_quote(list_token) == 1)
        return (1);
    remove_list_quotes(list_token);
    remove_empty_tokens(list_token);
    reunite_token(list_token);
    // print_list(list_token);
    return (0);
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;

    char *input;
    t_list **list_token;
    g_list_env = get_list_env(env);
   
    while (1)
    {
        signal(SIGQUIT, &ctrl_d);
        signal(SIGINT, &ctrl_c);
        input = get_input();
        list_token = malloc(sizeof(t_list));
        list_token[0] = NULL;
        if (init_list(list_token, input) == 0)
        {
            if (syntax_error(list_token) == 2)
                exec(list_token, g_list_env);
        }
        free_list(list_token);
    }
    free(input);
    free_list(g_list_env);
    return (0);
}
