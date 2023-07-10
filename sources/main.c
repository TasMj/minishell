/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:39:21 by tas               #+#    #+#             */
/*   Updated: 2023/07/10 16:42:03 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_list(t_minishell *data)
{
	data->token = create_token(data->token, data->input);
	if (err_quote(data->token, data) == 1)
		return (1);
	get_type(data->token);
	substitute_dollar(data);
	if (err_redir(data) != 3)
		return (1);
	remove_list_quotes(data->token);
	reunite_token(data->token);
	return (0);
}

t_minishell	*singleton_minishell(void)
{
	static t_minishell	*data = NULL;

	if (data == NULL)
	{
		data = (t_minishell *)malloc(sizeof(t_minishell));
		data->input = NULL;
		data->token = NULL;
		data->x = NULL;
	}
	return (data);
}

int	init_main(char **env, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	g_exit_code = 0;
	g_list_env = get_list_env(env);
	if (!g_list_env)
		return (perror("env malloc error\n"), 1);
	singleton_minishell()->code_err = 0;
	return (0);
}

void	executing(t_minishell *data)
{
	if (syntax_error(data) == 3)
		we_exec(data);
	set_signal();
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*data;

	data = singleton_minishell();
	if (init_main(env, argc, argv) == 1)
		return (1);
	while (1)
	{
		set_signal();
		data->input = get_input(data);
		if (data->input && space_only(data->input) == 0)
		{
			data->token = malloc(sizeof(t_list));
			*data->token = NULL;
			if (!data->input && !data->token[0])
				break ;
			if (init_list(data) == 0)
				executing(data);
			free_main_tools(data);
		}
	}
	free_list_token_content(g_list_env);
	return (free_list(g_list_env), 0);
}
