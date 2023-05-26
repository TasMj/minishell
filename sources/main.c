/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:39:21 by tas               #+#    #+#             */
/*   Updated: 2023/05/26 12:31:56 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

void    init_list(t_list **list_token, char *input)
{
    list_token = create_token(list_token, input);
    substitute_dollar(list_token);
    get_type(list_token);
    remove_list_quotes(list_token);
    del_empty_token(list_token);
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
        signal(SIGQUIT, SIG_IGN);
        // signal(SIGINT, &ctrl_c);
        input = get_input();
        list_token = malloc(sizeof(t_list));
        list_token[0] = NULL;
        init_list(list_token, input);
        if (syntax_error(list_token) == 2)
            exec(list_token, g_list_env);
        // exec_builtin(list_token);
    }
    return (0);
}
