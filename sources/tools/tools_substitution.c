/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_substitution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:34:52 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/05 22:52:49 by tmejri           ###   ########.fr       */
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

static char	*remove_dollar(char *str)
{
	int		i;
	int		j;
	char	*token;

	i = 0;
	j = 0;
	if (str[i])
	{
		i++;
		token = malloc(sizeof(char) * ft_strlen(str));
	}
	else
		return (NULL);
	while (str[i])
	{
		token[j] = str[i];
		i++;
		j++;
	}
	token[j] = '\0';
	return (token);
}

char	*substitution(t_minishell *data, char *token)
{
	char	*variable;
	char	*var_check;

	variable = NULL;
	if ((ft_strlen(token) == 2) && ft_strcmp(token, "$?") == 0)
		variable = ft_itoa(data->code_err);
	else if (token[0] == '$')
	{
		var_check = remove_dollar(token);
		if (is_in_env(var_check))
			variable = get_venv(var_check);
		else
			variable = "";
		free(var_check);
	}
	else if (!variable)
		variable = "";
	return (variable);
}

t_list	*ft_lst_prev(t_list *elem, t_list *first)
{
	t_list	*tmp;

	tmp = first;
	if (first == elem)
		return (NULL);
	while (first)
	{
		if (first->next == elem)
		{
			first = tmp;
			return (first);
		}
		first = first->next;
	}
	first = tmp;
	return (NULL);
}
