/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:39:21 by tas               #+#    #+#             */
/*   Updated: 2023/06/10 14:26:14 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

int    init_list(t_list **list_token, char *input)
{
    list_token = create_token(list_token, input);

    if (err_quote(list_token) == 1)
        return (1);
    substitute_dollar(list_token);
    get_type(list_token);
    // if (err_quote(list_token) == 1)
        // return (1);
    remove_list_quotes(list_token);
    remove_empty_tokens(list_token);
    reunite_token(list_token);
    print_list(list_token);
    return (0);
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    t_minishell data;

    g_list_env = get_list_env(env);
    while (1)
    {
        signal(SIGQUIT, &ctrl_d);
        signal(SIGINT, &ctrl_c);
        data.input = get_input();
        data.token = malloc(sizeof(t_list));
        *data.token = NULL;

        if (init_list(data.token, data.input) == 0)
        {
            if (syntax_error(data.token) == 2)
            {
                exec_builtin(data.token);
                // we_exec(&data);
                // exec(list_token, g_list_env);
            }
        }
        free_list_token_content(data.token);
        free_list(data.token);
        free(data.input);
    }
    free_list_token_content(g_list_env);
    free_list(g_list_env);
    printf("sortie\n");
    return (0);
}
