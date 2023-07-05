/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:19:12 by tas               #+#    #+#             */
/*   Updated: 2023/07/05 22:38:39 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	more_dollar(t_substitution *s, t_minishell *data)
{
	s->i = 0;
	while ((*data->token)->content[s->i])
	{
		go_to_dollar(s, data);
	}
	free((*data->token)->content);
	(*data->token)->content = ft_strdup(s->new_content);
}

void	without_quotes(t_minishell *data, t_substitution *s)
{
	if (ft_lst_prev(*data->token, s->starting) == NULL)
	{
		s->starting = s->reset;
		more_dollar(s, data);
	}
	else if (ft_lst_prev(*data->token, s->starting) != NULL
		&& ft_lst_prev(*data->token, s->starting)->type != HEREDOC)
	{
		s->starting = s->reset;
		more_dollar(s, data);
	}
}

void	init_s(t_substitution *s, t_minishell *data)
{
	ft_memset(s, 0, sizeof(t_substitution));
	s->starting = *data->token;
	s->reset = *data->token;
	s->tmp = *data->token;
	s->prev = NULL;
}

void	substitute_dollar(t_minishell *data)
{
	t_substitution	*s;

	s = malloc(sizeof(t_substitution));
	init_s(s, data);
	while ((*data->token) != NULL)
	{
		s->new_content = NULL;
		if (check_dollar((*data->token)->content) == 1)
		{
			if ((*data->token)->content[0] == 34)
				quote_sub(s, 1, data);
			else if ((*data->token)->content[0] == 39)
				quote_sub(s, 2, data);
			else if (ft_strlen((*data->token)->content) > 1)
				without_quotes(data, s);
			else if (ft_strlen((*data->token)->content) == 1)
				quotes_next_to_dollar(data, s);
		}
		if (s->new_content)
			free(s->new_content);
		s->prev = (*data->token);
		(*data->token) = (*data->token)->next;
	}
	*data->token = s->tmp;
	free(s);
}
