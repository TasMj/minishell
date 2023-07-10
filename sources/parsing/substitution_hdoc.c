/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution_hdoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:47:38 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/10 22:48:02 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_tmp(char *tmp, t_substitution *s)
{
	if (s->keep_var[s->end] != '\0')
	{
		s->start = s->end;
		while (s->keep_var[s->end] != '\0')
			s->end++;
		tmp = ft_strdup_size(s->keep_var + s->start, (s->end - s->start));
		tmp = ft_strjoin_mod(s->var_substitute, tmp, 2);
	}
	else
		tmp = ft_strdup(s->var_substitute);
	return (tmp);
}

void	sub_d_hdoc_annex(t_substitution *s, char *str, t_minishell *data)
{
	s->start = s->i;
	if ((s->i + 1) < ft_strlen((*data->token)->content))
		s->i++;
	while ((s->i <= ft_strlen(str)) && str[s->i] != '\0'
		&& (ft_isalnum(str[s->i]) || str[s->i] == '_'))
		s->i++;
	s->end = s->i;
	s->keep_var = ft_strdup_size(str + s->start, (s->end - s->start));
	s->var_substitute = substitution(s->keep_var, data);
	if (s->var_substitute && ft_strlen(s->var_substitute) != 0)
		s->new_content = ft_strjoin_mod(s->new_content, s->var_substitute, 3);
	else
		sub_rest(s, str);
	if (s->keep_var)
		free(s->keep_var);
}

void	sub_dollar_hdoc(t_substitution *s, char *str, t_minishell *data)
{
	s->deb = s->i;
	while (str[s->i] && str[s->i] != '$')
		s->i++;
	s->without_dollar = ft_strdup_size(str + s->deb, (s->i - s->deb));
	if (!s->new_content)
		s->new_content = ft_strdup(s->without_dollar);
	else
		s->new_content = ft_strjoin_mod(s->new_content, s->without_dollar, 1);
	if (str[s->i] && str[s->i] == '$' && str[s->i + 1] == '\0')
	{
		s->new_content = ft_strjoin_mod(s->new_content, "$", 0);
		s->i++;
	}
	else if (str[s->i] && str[s->i + 1] && str[s->i + 1] == '?')
		hdoc_exclam(s, str, data);
	else
		sub_d_hdoc_annex(s, str, data);
	if (s->without_dollar)
		free(s->without_dollar);
}
