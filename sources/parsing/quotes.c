/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:15:52 by tmejri            #+#    #+#             */
/*   Updated: 2023/05/27 13:05:18 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* check if there is a quote alone */
int	check_pair_quote(char *str)
{
	int		i;
	int		flag;
	char	quote;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			quote = str[i];
			flag = 1;
			while (str[i])
			{
				i++;
				if (str[i] == quote && flag == 1)
				{
					flag = 0;
					break ;
				}
			}
		}
		i++;
	}
	if (flag == 1)
		return (1);
	return (0);
}

/* check si après la première simple quote (') on trouve la deuxième
return 0 si pas de ', 1 si un seul ', 2 si on trouve la deuxième */
int	check_pair_single_quote(char *str)
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
int	check_pair_double_quote(char *str)
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

/* découpe le mot comme il faut pour les mots entre quote */
char	*word_quote(char *stockage, int quote)
{
	int		i;
	int		start;
	int		flag;
	char	*new;

	i = 0;
	flag = 0;
	start = 0;
	new = NULL;
	while (stockage[i] && flag < 2)
	{
		while (is_a_space(stockage[i]) == 1 || stockage[i] == quote)
		{
			if (stockage[i] == quote)
				flag++;
			i++;
		}
		start = i - 1;
		while (stockage[i] != quote)
			i++;
		if (stockage[i] == quote)
			flag++;
	}
	new = ft_strdup_size(stockage + start, ((i + 1) - start));
	return (new);
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

	tmp = (*list_token);
	while (*list_token)
	{
		if ((check_pair_double_quote((*list_token)->content) == 2
				|| check_pair_single_quote((*list_token)->content) == 2)
			&& (*list_token)->flag_quote != 1)
		{
			stockage = remove_quotes((*list_token)->content);
			free((*list_token)->content);
			(*list_token)->content = \
			ft_strdup_size(stockage, ft_strlen(stockage));
			free(stockage);
		}
		(*list_token) = (*list_token)->next;
	}
	(*list_token) = tmp;
}
