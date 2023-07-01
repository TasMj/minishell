/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:39:21 by tas               #+#    #+#             */
/*   Updated: 2023/07/01 12:35:56 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    init_list(t_minishell *data)
{
    data->token = create_token(data->token, data->input);
    if (err_quote(data->token) == 1)
        return (1);

    substitute_dollar(data);
    get_type(data->token);
    if (err_redir(data) != 3)
        return (1);
    remove_list_quotes(data->token);
    add_space(data);
    // print_list(data->token);
    remove_empty_tokens(data->token);
    // print_list(data->token);
    reunite_token(data->token);
    return (0);
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    t_minishell data;

    g_list_env = get_list_env(env);
    if (!g_list_env)
        return (perror("env malloc error\n"), 1);
    ft_memset(&data, 0, sizeof(t_minishell));
    set_signal();
    while (1)
    {
        data.input = get_input();
        data.token = malloc(sizeof(t_list));
        if (!data.token)
        {
            free_list_token_content(data.token);
            free_list(data.token);
            free(data.input);
            break ;
        }
        *data.token = NULL;
        if (init_list(&data) == 0)
        {
            if (!data.token || ft_lstsize(*(data.token)) == 0)
		        data.code_err = 0;
            else if (syntax_error(&data) == 3)
               we_exec(&data);
            // else if (syntax_error(&data) != 0 && syntax_error(&data) != 1)
                // data.code_err = 2;
        }
        free_list_token_content(data.token);
        free_list(data.token);
        free(data.input);
    }
    free_list_token_content(g_list_env);
    free_list(g_list_env);
    return (0);
}
