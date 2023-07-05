/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:39:21 by tas               #+#    #+#             */
/*   Updated: 2023/07/06 00:03:23 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    init_list(t_minishell *data)
{
    data->token = create_token(data->token, data->input);
    if (err_quote(data->token, data) == 1)
        return (1);
    get_type(data->token);
    substitute_dollar(data);
    if (err_redir(data) != 3)
        return (1);
    remove_list_quotes(data->token);
    // add_space(data);
    // remove_empty_tokens(data->token);
    reunite_token(data->token);
    return (0);
}

t_minishell *singleton_minishell(void)
{
    static t_minishell  *data = NULL;

    if (data == NULL)
    {
        data = (t_minishell *)malloc(sizeof(t_minishell));
        data->input = NULL;
        data->token = NULL;
        data->x = NULL;
    }
    return (data);
}

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ' || c == '\0')
		return (1);
	else
		return (0);
}

int	space_only(char *p)
{
	char	*char_ptr;

	char_ptr = p;
	if (char_ptr != NULL)
	{
		while (*char_ptr)
		{
			if (ft_isspace(*char_ptr))
				char_ptr++;
			else
				return (0);
		}
		return (1);
	}
	else
		return (1);
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    t_minishell *data;

    g_list_env = get_list_env(env);
    if (!g_list_env)
        return (perror("env malloc error\n"), 1);
    data = singleton_minishell();
    data->code_err = 0;
    while (1)
    {
        set_signal();
        data->input = get_input(data);
        if (data->input && space_only(data->input) == 0)
        {
            data->token = malloc(sizeof(t_list));
            *data->token = NULL;
            if (!data->input && !data->token[0])
            {
                break ;
            }
            if (init_list(data) == 0)
            {
                data->code_err = 0;
                if (syntax_error(data) == 3)
                {
                    we_exec(data);
                    set_signal();
                }
            }
            free_list_token_content(data->token);
            free_list(data->token);
            free(data->input);
        }
    }
    free_list_token_content(g_list_env);
    free_list(g_list_env);
    return (0);
}
