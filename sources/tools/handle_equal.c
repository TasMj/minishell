/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_equal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:43:39 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/10 22:06:10 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	check_list_equal(t_list **list)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *list;
	while (*list)
	{
		if (check_equal((*list)->content) == 1)
			i++;
		(*list) = (*list)->next;
	}
	*list = tmp;
	return (i);
}

char	*del_equal(char *str)
{
	int		i;
	char	*var;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var = ft_strdup_size(str, i);
	return (var);
}

char	*after_equal(char *str)
{
	int		i;
	int		start;
	char	*var;

	if (check_equal(str) == 0)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if ((i + 1) == ft_strlen(str))
	{
		return (NULL);
	}
	if (str[i] && str[i] == '=')
		i++;
	start = i;
	while (str[i])
		i++;
	var = ft_strdup_size(str + start, (i - start));
	return (var);
}

int	is_in_env(char *str, t_minishell *data)
{
	t_list	*tmp;
	char	*copy;

	tmp = *data->env;
	while (*data->env)
	{
		copy = del_equal((*data->env)->content);
		if (ft_strcmp(str, copy) == 0)
		{
			free(copy);
			*data->env = tmp;
			return (1);
		}
		free(copy);
		(*data->env) = (*data->env)->next;
	}
	*data->env = tmp;
	return (0);
}
