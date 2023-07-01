/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:47:38 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/01 18:45:54 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*substitution(t_minishell *data, char *token)
{
	char	*variable;

	variable = NULL;
	if ((ft_strlen(token) == 2) && ft_strcmp(token, "$?") == 0)
	{
		variable = ft_itoa(data->code_err);
	}
	else if (is_in_env(token + 1))
		variable = get_venv(token + 1);
	else if (!variable)
		variable = "";
	return (variable);
}

void	quote_sub(t_substitution *s, int a, t_minishell *data)
{
	if (a == 1)
		s->var_substitute = sub_quotes((*data->token)->content, s, data);
	else if (a == 2)
		s->var_substitute = remove_quotes((*data->token)->content);
	free((*data->token)->content);
	(*data->token)->content = ft_strdup(s->var_substitute);
	(*data->token)->flag_quote = 1;
	// free(s->new_content);
}

char	*remove_quote_end(t_substitution *s, t_minishell *data)
{
	int		i;
	char	*var_modif;
	char	*tmp;

	i = 0;
	while (s->keep_var[i] && s->keep_var[i] != 39 && s->keep_var[i] != 34)
		i++;
	if (i != ft_strlen(s->keep_var))
		s->flag_keep_quote = 1;
	tmp = ft_strdup_size(s->keep_var, i);
	var_modif = substitution(data, tmp);
	free(tmp);
	if (ft_strlen(var_modif) != 0)
		var_modif = ft_strjoin_mod(var_modif, s->keep_var + i, 1);
	return (var_modif);
}
