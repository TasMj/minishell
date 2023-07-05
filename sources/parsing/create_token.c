/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:36:17 by tas               #+#    #+#             */
/*   Updated: 2023/07/05 06:25:03 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_input(t_minishell *data)
{
	(void) data;
	char	*input;
	// char	cwd[1024];
	char	*prompt;
	char	*code;

	// prompt = ft_strdup(getcwd(cwd, sizeof(cwd)));
	// prompt = ft_strjoin_mod("\033[1;33m", prompt, 2);
	// prompt = ft_strjoin_mod(prompt, "\033[0m", 1);
	// prompt = ft_strjoin_mod(prompt, "$> ", 1);
	code = ft_itoa(data->code_err);
	if (data->code_err == 0)
	{
		prompt = ft_strdup("[");
		prompt = ft_strjoin_mod(prompt, code, 1);
		prompt = ft_strjoin_mod(prompt, "]\033[1;32m> \033[0m", 1);
	}
	else
	{
		prompt = ft_strdup("[\033[1;31m");
		prompt = ft_strjoin_mod(prompt, code, 1);
		prompt = ft_strjoin_mod(prompt, "\033[0m]\033[1;32m> \033[0m", 1);
	// prompt = ft_strdup("> ");
	}
	free(code);
	// prompt = ft_strdup("\033[1;32m$> \033[0m");
	input = readline(prompt); 
	free(prompt);
	if (input == NULL)
	{
		free(input);
		write(1, "exit\n", 5);
		free_list_token_content(g_list_env);
		free_list(g_list_env);
		free(data);
		exit(EXIT_FAILURE);
	}
	else if (input && *input)
		add_history(input);
	return (input);
}

static void	delimit_operator(t_substitution *s, char *input)
{
	if (input[s->i] == '|' || input[s->i] == '>' || input[s->i] == '<')
	{
		s->i++;
		if (input[s->i] == '>' || input[s->i] == '<')
			s->i++;
	}
	else if (is_a_separator(input[s->i]) == 1)
	{
		while (input[s->i] && input[s->i] != 39 && input[s->i] != 34)
			s->i++;
	}
	else if (input[s->i] == '$' && input[s->i + 1] && input[s->i + 1] == '?')
		s->i+=2;
	else
	{
		while (is_a_separator(input[s->i]) == 0
			&& input[s->i] != 39 && input[s->i] != 34)
			s->i++;
	}
}

static void	delimit_token(t_substitution *s, char *input)
{
	if (input[s->i] == 39 || input[s->i] == 34)
	{
		s->quote = input[s->i];
		s->flag = 1;
		s->i++;
		while (input[s->i] && input[s->i] != s->quote && s->flag == 1)
			s->i++;
		s->flag = 0;
		s->i++;
	}
	else
		delimit_operator(s, input);
}

static void	add_token(t_list **list_token, t_substitution *s, char *input)
{
	s->start = s->i;
	delimit_token(s, input);
	s->end = s->i;
	if (s->flag == 1)
		s->i++;
	s->stock = ft_strdup_size(input + s->start, (s->end - s->start));
	if (s->flag_space == 1)
	{
		add_list(list_token, s->stock, 1);
		s->flag_space = 0;
	}
	else
		add_list(list_token, s->stock, 0);
}

t_list	**create_token(t_list **list_token, char *input)
{
	t_substitution	*s;

	s = malloc(sizeof(t_substitution));
	ft_memset(s, 0, sizeof(t_substitution));
	while (s->i < ft_strlen(input))
	{
		if (is_a_space(input[s->i]) == 1)
		{
			s->i++;
			s->flag_space = 1;
		}
		else
			add_token(list_token, s, input);
	}
	free(s);
	return (list_token);
}
