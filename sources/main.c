/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:39:21 by tas               #+#    #+#             */
/*   Updated: 2023/05/16 18:00:32 by tmejri           ###   ########.fr       */
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
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    (void)env;

    char *input;
    t_list **list_token;
    list_ENVI = get_list_env(env);
    while(1)
    {
        signal(SIGQUIT, SIG_IGN);
        signal(SIGINT, &ctrl_c);
        input = get_input();
        list_token = malloc(sizeof(t_list));
        list_token[0] = NULL;
        init_list(list_token, input);
        syntax_error(list_token);

        if (creating_process(list_token, env) == 1)
            break ;
    }
    return (0);
}
