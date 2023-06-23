/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:15:52 by tmejri            #+#    #+#             */
/*   Updated: 2023/06/23 12:33:56 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pair_quote(char *str)
{
	t_substitution	s;

	s.i = 0;
	s.flag = 0;
	while (str[s.i])
	{
		if (str[s.i] == 39 || str[s.i] == 34)
		{
			s.quote = str[s.i];
			s.flag = 1;
			while (str[s.i])
			{
				s.i++;
				if (str[s.i] == s.quote && s.flag == 1)
				{
					s.flag = 0;
					break ;
				}
			}
		}
		s.i++;
	}
	if (s.flag == 1)
		return (1);
	return (0);
}

/* check si après la première simple quote (') on trouve la deuxième
return 0 si pas de ', 1 si un seul ', 2 si on trouve la deuxième */
static int	check_pair_single_quote(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == 39)
		{
			flag = 1;
			while (str[i])
			{
				i++;
				if (str[i] == 39 && flag == 1)
					return (2);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

/* check si après la première simple quote (") on trouve la deuxième
return 0 si pas de ", 1 si un seul ", 2 si on trouve la deuxième */
static int	check_pair_double_quote(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == 34)
		{
			flag = 1;
			while (str[i])
			{
				i++;
				if (str[i] == 34 && flag == 1)
					return (2);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

char	*remove_quotes(char *str)
{
	char	*new_str;

	new_str = ft_strdup_size(str + 1, ft_strlen(str) - 2);
	return (new_str);
}

/* if token is in quote, remove the quote */
void	remove_list_quotes(t_list **list_token)
{
	t_list	*tmp;
	char	*stockage;

	tmp = *list_token;
	while (*list_token)
	{
		if ((check_pair_double_quote((*list_token)->content) == 2
				|| check_pair_single_quote((*list_token)->content) == 2)
			&& (*list_token)->flag_quote != 1)
		{
			stockage = remove_quotes((*list_token)->content);
			free((*list_token)->content);
			(*list_token)->content = ft_strdup(stockage);
			free(stockage);
		}
		(*list_token) = (*list_token)->next;
	}
	(*list_token) = tmp;
}
