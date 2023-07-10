/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution_hdoc2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:01:33 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/10 20:14:01 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hdoc_exclam(t_substitution *s, char *str)
{
	int		deb;
	char	*tmp;

	s->start = s->i;
	s->i += 2;
	s->end = s->i;
	s->keep_var = ft_strdup_size(str + s->start, (s->end - s->start));
	s->var_substitute = substitution(s->keep_var);
	deb = s->i;
	s->new_content = ft_strjoin_mod(s->new_content, s->var_substitute, 3);
	while (str[s->i] != '\0' && (!ft_isalnum(str[s->i]) && str[s->i] != '$'))
			s->i++;
	tmp = ft_strdup_size(str + deb, (s->i - deb));
	s->new_content = ft_strjoin_mod(s->new_content, tmp, 3);
	free(s->keep_var);
}

void	hdoc_rest(t_substitution *s, char *str, t_minishell *data)
{
	int		deb;
	char	*tmp;

	s->start = s->i;
	if ((s->i + 1) < ft_strlen((*data->token)->content))
		s->i++;
	while (str[s->i] != '\0' && (ft_isalnum(str[s->i]) || str[s->i] == '_'))
		s->i++;
	s->end = s->i;
	s->keep_var = ft_strdup_size(str + s->start, (s->end - s->start));
	s->var_substitute = substitution(s->keep_var);
	if (ft_strlen(s->var_substitute) != 0)
		s->new_content = ft_strjoin_mod(s->new_content, s->var_substitute, 3);
	else
	{
		deb = s->i;
		s->new_content = ft_strjoin_mod(s->new_content, "", 1);
		while ((s->i <= ft_strlen(str)) && str[s->i] != '\0'
			&& (!ft_isalnum(str[s->i]) && str[s->i] != '$'))
			s->i++;
		tmp = ft_strdup_size(str + deb, (s->i - deb));
		s->new_content = ft_strjoin_mod(s->new_content, tmp, 3);
	}
	if (s->keep_var)
		free(s->keep_var);
}

void	sub_dol_annex(t_substitution *s, char *str)
{
	int		deb;
	char	*tmp;

	deb = s->i;
	s->new_content = ft_strjoin_mod(s->new_content, "", 1);
	while ((s->i <= ft_strlen(str)) && str[s->i] != '\0'
		&& (!ft_isalnum(str[s->i]) && str[s->i] != '$'))
		s->i++;
	tmp = ft_strdup_size(str + deb, (s->i - deb));
	s->new_content = ft_strjoin_mod(s->new_content, tmp, 3);
}

void	sub_dol_hdox_bis(t_substitution *s, char *str, t_minishell *data)
{
	s->start = s->i;
	if ((s->i + 1) < ft_strlen((*data->token)->content))
		s->i++;
	while ((s->i <= ft_strlen(str)) && str[s->i] != '\0'
		&& (ft_isalnum(str[s->i]) || str[s->i] == '_'))
		s->i++;
	s->end = s->i;
	s->keep_var = ft_strdup_size(str + s->start, (s->end - s->start));
	s->var_substitute = substitution(s->keep_var);
	if (s->var_substitute && ft_strlen(s->var_substitute) != 0)
		s->new_content = ft_strjoin_mod(s->new_content, s->var_substitute, 3);
	else
		sub_dol_annex(s, str);
	if (s->keep_var)
		free(s->keep_var);
}

void	sub_rest(t_substitution *s, char *str)
{
	int		deb;
	char	*tmp;

	deb = s->i;
	s->new_content = ft_strjoin_mod(s->new_content, "", 1);
	while ((s->i <= ft_strlen(str)) && str[s->i] != '\0'
		&& (!ft_isalnum(str[s->i]) && str[s->i] != '$'))
		s->i++;
	tmp = ft_strdup_size(str + deb, (s->i - deb));
	s->new_content = ft_strjoin_mod(s->new_content, tmp, 3);
}
