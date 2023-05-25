/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:19:12 by tas               #+#    #+#             */
/*   Updated: 2023/05/25 17:27:42 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

void	go_to_dollar(t_substitution *s, t_list *tok)
{
	s->deb = s->i;
	while (tok->content[s->i] && tok->content[s->i] != '$')
		s->i++;
	s->without_dollar = ft_strdup_size(tok->content + s->deb, (s->i - s->deb));
	s->new_content = ft_strjoin_mod(s->new_content, s->without_dollar, 2);
	if (tok->content[s->i] && tok->content[s->i] == '$'
		&& tok->content[s->i + 1] == '\0')
	{
		s->new_content = ft_strjoin_mod(s->new_content, "$", 0);
		s->i++;
	}
	else
	{
		s->start = s->i;
		s->i++;
		while (tok->content[s->i] != '\0' && tok->content[s->i] != '$')
			s->i++;
		s->end = s->i;
		s->keep_var = ft_strdup_size(tok->content + s->start, \
		(s->end - s->start));
		s->var_substitute = ft_strdup_size(substitution(s->keep_var), \
		ft_strlen(substitution(s->keep_var)));
		s->new_content = ft_strjoin_mod(s->new_content, s->var_substitute, 2);
	}
}

void	more_dollar(t_substitution *s, t_list **list_token)
{
	s->i = 0;
	s->new_content = "";
	while ((*list_token)->content[s->i])
		go_to_dollar(s, (*list_token));
	free((*list_token)->content);
	(*list_token)->content = ft_strdup_size(s->new_content, \
	ft_strlen(s->new_content));
	free(s->new_content);
}

void	substitute_dollar(t_list **list_token)
{
	t_substitution	*s;
	t_list			*tmp;

	s = malloc(sizeof(t_substitution));
	tmp = *list_token;
	s->new_content = "";
	while ((*list_token) != NULL)
	{
		if (check_dollar((*list_token)->content) == 1)
		{
			if ((*list_token)->content[0] == 34)
				quote_sub(s, (*list_token), 1);
			else if ((*list_token)->content[0] == 39)
				quote_sub(s, (*list_token), 2);
			else if (ft_strlen((*list_token)->content) > 1)
				more_dollar(s, list_token);
		}
		(*list_token) = (*list_token)->next;
	}
	*list_token = tmp;
}

char	*sub_quotes(char *token, t_substitution *s)
{
	s->i = 0;
	s->new_content = "";
	s->stock = remove_quotes(token);
	while (s->stock[s->i])
	{
		s->deb = s->i;
		while (s->stock[s->i] && s->stock[s->i] != '$')
			s->i++;
		s->without_dollar = ft_strdup_size(s->stock + s->deb, (s->i - s->deb));
		s->new_content = ft_strjoin_mod(s->new_content, s->without_dollar, 2);
		if (s->stock[s->i] && s->stock[s->i] == '$' && \
		(is_a_space(s->stock[s->i + 1]) == 1 || s->stock[s->i + 1] == '\0'))
		{
			s->new_content = ft_strjoin_mod(s->new_content, "$", 1);
			s->i++;
		}
		else if (s->stock[s->i] && s->stock[s->i + 1] && s->stock[s->i] == '$'
			&& (is_a_space(s->stock[s->i + 1]) == 0
				|| s->stock[s->i + 1] != '\0'))
		{
			s->start = s->i;
			s->i++;
			while (is_a_space(s->stock[s->i]) == 0
				&& s->stock[s->i] != '\0' && s->stock[s->i] != '$')
				s->i++;
			s->end = s->i;
			s->keep_var = ft_strdup_size(s->stock + s->start, \
			(s->end - s->start));
			s->keep_var2 = ft_strdup_size(substitution(s->keep_var), \
			ft_strlen(substitution(s->keep_var)));
			s->new_content = ft_strjoin_mod(s->new_content, s->keep_var2, 2);
		}
	}
	return (s->new_content);
}
