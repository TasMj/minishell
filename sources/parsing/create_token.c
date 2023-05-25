/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:36:17 by tas               #+#    #+#             */
/*   Updated: 2023/05/25 15:05:02 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* read and stock input */
char	*get_input(void)
{
	char	*input;
	char	cwd[1024];
	char	*prompt;

	prompt = ft_strdup_size(getcwd(cwd, sizeof(cwd)) + 5, \
	ft_strlen(getcwd(cwd, sizeof(cwd)) + 5));
	prompt = ft_strjoin_mod("\033[1;33m", prompt, 0);
	prompt = ft_strjoin_mod(prompt, "\033[0m", 0);
	prompt = ft_strjoin_mod(prompt, "$> ", 0);
	input = readline(prompt);
	free(prompt);
	if (input == NULL)
		exit(EXIT_FAILURE);
	else
		add_history(input);
	return (input);
}

void	delimit_size_operator(t_substitution *s, char *input)
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
	else
	{
		while (is_a_separator(input[s->i]) == 0
			&& input[s->i] != 39 && input[s->i] != 34)
			s->i++;
	}
}

void	delimit_token(t_substitution *s, char *input)
{
	if (input[s->i] == 39 || input[s->i] == 34)
	{
		s->quote = input[s->i];
		s->flag = 1;
		s->i++;
		while (input[s->i] != s->quote && s->flag == 1)
			s->i++;
		s->flag = 0;
		s->i++;
	}
	else
		delimit_size_operator(s, input);
}

void	set_token(t_list **list_token, t_substitution *s, char *input)
{
	// s->start = s->i;
	// delimit_token(s, input);
	// s->end = s->i;
	if (s->flag == 1)
		s->i++;
	s->stockage = ft_strdup_size(input + s->start, (s->end - s->start));
	if (s->flag_space == 1)
	{
		add_list(list_token, s->stockage, 1);
		s->flag_space = 0;
	}
	else
		add_list(list_token, s->stockage, 0);
}

t_list	**create_token(t_list **list_token, char *input)
{
	t_substitution	*s;

	s = malloc(sizeof(t_substitution));
	ft_memset(s, 0, sizeof(t_substitution));
	s->i = 0;
	s->start = 0;
	s->end = 0;
	s->flag = 0;
	s->flag_space = 0;
	while (s->i < ft_strlen(input))
	{
		if (is_a_space(input[s->i]) == 1)
		{
			s->i++;
			s->flag_space = 1;
		}
		else
		{
			// set_token(list_token, s, input);
			s->start = s->i;
			delimit_token(s, input);
			s->end = s->i;
			if (s->flag == 1)
				s->i++;
			s->stockage = ft_strdup_size(input + s->start, (s->end - s->start));
			if (s->flag_space == 1)
			{
				add_list(list_token, s->stockage, 1);
				s->flag_space = 0;
			}
			else
				add_list(list_token, s->stockage, 0);
		}
	}
	return (list_token);
}
