/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:47:38 by tmejri            #+#    #+#             */
/*   Updated: 2023/05/28 00:48:17 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

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

char	*remove_space(char *str)
{
	int		i;
	int		start;
	int		end;
	char	*stockage;

	i = 0;
	while (is_a_space(str[i]) == 1)
		i++;
	start = i;
	while (is_a_space(str[i]) == 0)
		i++;
	end = i;
	stockage = ft_strdup_size(str + start, (end - start));
	return (stockage);
}

char	*substitution(char *token)
{
	char	*variable;

	variable = NULL;
	if (is_in_env(token + 1))
		variable = get_venv(token + 1);
	if (!variable)
	{
		variable = malloc(1);
		variable = "";
	}
	return (variable);
}

void	quote_sub(t_substitution *s, t_list *list_token, int a)
{
	if (a == 1)
		s->var_substitute = sub_quotes(list_token->content, s);
	else if (a == 2)
		s->var_substitute = remove_quotes(list_token->content);
	free(list_token->content);
	list_token->content = ft_strdup(s->var_substitute); //
	list_token->flag_quote = 1;
	// free_substitution(s);
}

char	*remove_quote_end(t_substitution *s)
{
	int		i;
	char	*var_modif;

	i = 0;
	while (s->keep_var[i] && s->keep_var[i] != 39 && s->keep_var[i] != 34)
		i++;
	if (i != ft_strlen(s->keep_var))
		s->flag_keep_quote = 1;
	var_modif = substitution(ft_strdup_size(s->keep_var, i));
	var_modif = ft_strjoin(var_modif, s->keep_var + i);
	return (var_modif);
}
