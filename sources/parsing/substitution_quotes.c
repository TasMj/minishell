/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:29:07 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/10 22:45:41 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quotes_next_to_dollar(t_minishell *data, t_substitution *s)
{
	if (!(!(*data->token)->next && (*data->token)->content[0] == '$')
		&& (!((*data->token)->next->content && (*data->token)->content[0] == '$'
				&& (*data->token)->next->flag_space == 1))
		&& (*data->token)->next->content && (*data->token)->content[0] == '$'
		&& (*data->token)->next->flag_space == 0)
	{
		if (s->prev != NULL)
		{
			s->prev->next = (*data->token)->next;
			(*data->token)->next->flag_space = (*data->token)->flag_space;
			free((*data->token)->content);
			free(*data->token);
			(*data->token) = s->prev;
		}
		else
		{
			s->tmp = (*data->token)->next;
			free ((*data->token)->content);
			free(*data->token);
			(*data->token) = s->tmp;
		}
	}
}

void	delim_exclam(t_substitution *s, t_minishell *data)
{
	char	*tmp;
	int		deb;

	s->start = s->i;
	s->i += 2;
	s->end = s->i;
	s->keep_var = ft_strdup_size(s->stock + s->start, (s->end - s->start));
	s->keep_var2 = remove_quote_end(s, data);
	deb = s->i;
	s->new_content = ft_strjoin_mod(s->new_content, s->keep_var2, 3);
	while (s->stock[s->i] != '\0' && (!ft_isalnum(s->stock[s->i])
			&& s->stock[s->i] != '$'))
			s->i++;
	tmp = ft_strdup_size(s->stock + deb, (s->i - deb));
	s->new_content = ft_strjoin_mod(s->new_content, tmp, 3);
	free(s->keep_var);
}

void	delim_rest(t_substitution *s, t_minishell *data)
{
	s->start = s->i;
	s->i++;
	while (is_a_space(s->stock[s->i]) == 0
		&& s->stock[s->i] != '\0' && s->stock[s->i] != '$')
		s->i++;
	s->end = s->i;
	s->keep_var = ft_strdup_size(s->stock + s->start, (s->end - s->start));
	s->keep_var2 = remove_quote_end(s, data);
	if (ft_strlen(s->keep_var2) != 0)
		s->new_content = ft_strjoin_mod(s->new_content, s->keep_var2, 3);
	else
		free(s->keep_var2);
	free(s->keep_var);
}

static void	delimit_sub(t_substitution *s, t_minishell *data)
{
	if (s->stock[s->i] && s->stock[s->i] == '$'
		&& (is_a_space(s->stock[s->i + 1]) == 1 || s->stock[s->i + 1] == '\0'))
	{
		s->new_content = ft_strjoin_mod(s->new_content, "$", 1);
		s->i++;
	}
	else if (s->stock[s->i] && s->stock[s->i] == '$'
		&& s->stock[s->i + 1] && s->stock[s->i + 1] == '?')
		delim_exclam(s, data);
	else if (s->stock[s->i] && s->stock[s->i + 1] && s->stock[s->i] == '$'
		&& (is_a_space(s->stock[s->i + 1]) == 0
			|| s->stock[s->i + 1] != '\0'))
		delim_rest(s, data);
}

void	in_substitution(t_substitution *s, t_minishell *data)
{
	s->deb = s->i;
	while (s->stock[s->i] && s->stock[s->i] != '$')
		s->i++;
	s->without_dollar = ft_strdup_size(s->stock + s->deb, (s->i - s->deb));
	if (!s->new_content)
	{
		if (s->without_dollar)
		{
			s->new_content = ft_strdup(s->without_dollar);
			free(s->without_dollar);
		}
	}
	else
	{
		if (s->without_dollar)
			s->new_content = ft_strjoin_mod(s->new_content, \
			s->without_dollar, 3);
	}
	delimit_sub(s, data);
}
