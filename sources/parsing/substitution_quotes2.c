/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution_quotes2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:31:39 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/10 20:13:08 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*sub_quotes(char *token, t_substitution *s)
{
	char	*to_return;

	s->i = 0;
	s->stock = remove_quotes(token);
	while (s->stock[s->i])
		in_substitution(s);
	free(s->stock);
	to_return = ft_strdup(s->new_content);
	return (to_return);
}

void	quote_sub(t_substitution *s, int a, t_minishell *data)
{
	if (a == 1)
		s->var_substitute = sub_quotes((*data->token)->content, s);
	else if (a == 2)
		s->var_substitute = remove_quotes((*data->token)->content);
	free((*data->token)->content);
	(*data->token)->content = ft_strdup(s->var_substitute);
	(*data->token)->flag_quote = 1;
	free(s->var_substitute);
}

void	remov_quote_bis(t_substitution *s, int i)
{
	while (ft_isalnum(s->keep_var[i]))
		i++;
	s->end = i;
	s->keep_var2 = ft_strdup_size(s->keep_var, s->end);
	s->var_substitute = substitution(s->keep_var2);
	free(s->keep_var2);
}

char	*remove_quote_end(t_substitution *s)
{
	int		i;
	char	*tmp;

	i = 1;
	tmp = NULL;
	if (ft_strncmp(s->keep_var, "$?", 2) == 0)
		s->var_substitute = substitution("$?");
	else
		remov_quote_bis(s, i);
	tmp = set_tmp(tmp, s);
	if (ft_strlen(s->var_substitute) > 0)
		free(s->var_substitute);
	return (tmp);
}
