/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:19:12 by tas               #+#    #+#             */
/*   Updated: 2023/06/19 18:52:26 by tmejri           ###   ########.fr       */
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
	s->new_content = ft_strjoin_mod(s->new_content, s->without_dollar, 0);
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
		s->var_substitute = substitution(s->keep_var);
		if (ft_strlen(s->var_substitute) != 0)
			s->new_content = ft_strjoin_mod(s->new_content, s->var_substitute, 3);
		free(s->keep_var);
	}
	free(s->without_dollar);
}

void	more_dollar(t_substitution *s, t_list **list_token)
{
	s->i = 0;
	while ((*list_token)->content[s->i])
		go_to_dollar(s, (*list_token));
	free((*list_token)->content);
	(*list_token)->content = ft_strdup(s->new_content);
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
	free(s);
}

void	delimit_sub(t_substitution *s)
{
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
		s->keep_var2 = remove_quote_end(s);
		if (ft_strlen(s->keep_var2) != 0)
			s->new_content = ft_strjoin_mod(s->new_content, s->keep_var2, 3); //
		free(s->keep_var);
	}
}

char	*sub_quotes(char *token, t_substitution *s)
{
	s->i = 0;
	s->stock = remove_quotes(token);
	while (s->stock[s->i])
	{
		s->deb = s->i;
		while (s->stock[s->i] && s->stock[s->i] != '$')
			s->i++;
		s->without_dollar = ft_strdup_size(s->stock + s->deb, (s->i - s->deb));
		// if (!ft_strcmp(s->new_content, ""))
		if (ft_strlen(s->new_content) == 0)
			s->new_content = ft_strjoin_mod(s->new_content, s->without_dollar, 2);
		else
			s->new_content = ft_strjoin_mod(s->new_content, s->without_dollar, 3);
		delimit_sub(s);
	}
	free(s->stock);
	return (s->new_content);
}
