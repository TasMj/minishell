/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:08:46 by tmejri            #+#    #+#             */
/*   Updated: 2023/05/26 11:47:50 by tmejri           ###   ########.fr       */
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

char	*take_off_equal(char *str)
{
	int		i;
	char	*var;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var = ft_strdup_size(str, i);
	return (var);
}

int	is_in_env(char *str)
{
	t_list	*tmp;

	tmp = *g_list_env;
	while (*g_list_env)
	{
		if (ft_strcmp(str, take_off_equal((*g_list_env)->content)) == 0)
			return (1);
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