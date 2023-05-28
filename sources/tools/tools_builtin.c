/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:08:46 by tmejri            #+#    #+#             */
/*   Updated: 2023/05/28 17:03:52 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

int	count_slash(char *str)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '/')
			counter++;
		i++;
	}
	return (counter);
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

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] && str[i] == '=')
		i++;
	start = i;
	while (str[i])
		i++;
	var = ft_strdup_size(str + start, (i - start));
	return (var);
}

int	is_in_env(char *str)
{
	t_list	*tmp;
	char	*copy;

	tmp = *g_list_env;
	while (*g_list_env)
	{
		copy = del_equal((*g_list_env)->content);
		if (ft_strcmp(str, copy) == 0)
		{
			free(copy);
			*g_list_env = tmp;
			return (1);
		}
		free(copy);
		(*g_list_env) = (*g_list_env)->next;
	}
	*g_list_env = tmp;
	return (0);
}

t_list	**ft_copy_list(t_list **copy)
{
	while (*g_list_env)
	{
		add_list(copy, (*g_list_env)->content, 0);
		(*g_list_env) = (*g_list_env)->next;
	}
	return (copy);
}
