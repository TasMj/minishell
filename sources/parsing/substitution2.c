/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:37:35 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/10 22:39:51 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_to_code_err(t_substitution *s, t_minishell *data)
{
	int		deb;
	char	*tmp;

	s->start = s->i;
	s->i += 2;
	s->end = s->i;
	s->keep_var = ft_strdup_size((*data->token)->content + s->start, \
	(s->end - s->start));
	s->var_substitute = substitution(s->keep_var, data);
	deb = s->i;
	s->new_content = ft_strjoin_mod(s->new_content, s->var_substitute, 3);
	while ((*data->token)->content[s->i] != '\0'
		&& (!ft_isalnum((*data->token)->content[s->i]) && \
		(*data->token)->content[s->i] != '$'))
			s->i++;
	tmp = ft_strdup_size((*data->token)->content + deb, (s->i - deb));
	s->new_content = ft_strjoin_mod(s->new_content, tmp, 3);
	free(s->keep_var);
}

void	go_to_rest_bis(int deb, t_minishell *data, t_substitution *s)
{
	char	*tmp;

	s->new_content = ft_strjoin_mod(s->new_content, "", 1);
	tmp = ft_strdup_size((*data->token)->content + deb, (s->i - deb));
	while ((*data->token)->content[s->i] != '\0'
		&& (!ft_isalnum((*data->token)->content[s->i])
			&& (*data->token)->content[s->i] != '$'))
		s->i++;
	s->new_content = ft_strjoin_mod(s->new_content, tmp, 3);
}

void	go_to_rest(t_substitution *s, t_minishell *data)
{
	int		deb;

	s->start = s->i;
	if ((s->i + 1) < ft_strlen((*data->token)->content))
		s->i++;
	while ((*data->token)->content[s->i] != '\0'
		&& (ft_isalnum((*data->token)->content[s->i])
			|| (*data->token)->content[s->i] == '_'))
		s->i++;
	s->end = s->i;
	s->keep_var = ft_strdup_size((*data->token)->content + s->start, \
	(s->end - s->start));
	s->var_substitute = substitution(s->keep_var, data);
	if (s->var_substitute && ft_strlen(s->var_substitute) != 0)
		s->new_content = ft_strjoin_mod(s->new_content, s->var_substitute, 3);
	else
	{
		deb = s->i;
		go_to_rest_bis(deb, data, s);
	}
	if (s->keep_var)
		free(s->keep_var);
}

void	go_to_dollar(t_substitution *s, t_minishell *d)
{
	s->deb = s->i;
	while ((*d->token)->content[s->i] && (*d->token)->content[s->i] != '$')
		s->i++;
	s->without_dollar = ft_strdup_size((*d->token)->content + s->deb, \
	(s->i - s->deb));
	if (!s->new_content)
		s->new_content = ft_strdup(s->without_dollar);
	else
		s->new_content = ft_strjoin_mod(s->new_content, s->without_dollar, 1);
	if ((*d->token)->content[s->i] && (*d->token)->content[s->i] == '$'
		&& (*d->token)->content[s->i + 1] == '\0')
	{
		s->new_content = ft_strjoin_mod(s->new_content, "$", 0);
		s->i++;
	}
	else if ((*d->token)->content[s->i] && (*d->token)->content[s->i + 1]
		&& (*d->token)->content[s->i + 1] == '?')
		go_to_code_err(s, d);
	else
		go_to_rest(s, d);
	if (s->without_dollar)
		free(s->without_dollar);
}
