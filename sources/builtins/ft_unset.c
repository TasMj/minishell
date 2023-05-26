/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:11:35 by tas               #+#    #+#             */
/*   Updated: 2023/05/26 11:47:50 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

char	*var_name(char *str)
{
	char	*stockage;
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	stockage = ft_strdup_size(str, i);
	return (stockage);
}

int	check_var(char *str)
{
	t_list	*tmp;

	tmp = *g_list_env;
	while (*g_list_env)
	{
		if (ft_strcmp(var_name((*g_list_env)->content), str) == 0)
		{
			*g_list_env = tmp;
			return (1);
		}
		(*g_list_env) = (*g_list_env)->next;
	}
	*g_list_env = tmp;
	return (0);
}

void	del(char *str)
{
	t_list	*tmp_first;
	t_list	*tmp_next;

	tmp_first = *g_list_env;
	if (ft_strcmp(var_name((*g_list_env)->content), str) == 0)
	{
		(*g_list_env) = (*g_list_env)->next;
		tmp_first = *g_list_env;
	}
	else
	{
		while ((*g_list_env)->next != NULL
			&& ft_strcmp(var_name((*g_list_env)->next->content), str) == 1)
			(*g_list_env) = (*g_list_env)->next;
		tmp_next = (*g_list_env)->next->next;
		(*g_list_env)->next = tmp_next;
	}
	*g_list_env = tmp_first;
}

int	ft_unset(t_list **list_token)
{
	t_list	*tmp;

	tmp = *g_list_env;
	if (ft_strncmp((*list_token)->content, "unset", 5) == 1)
		return (1);
	else
	{
		(*list_token) = (*list_token)->next;
		while (*list_token != NULL)
		{
			if (check_var((*list_token)->content) == 1)
				del((*list_token)->content);
			(*list_token) = (*list_token)->next;
		}
	}
	*g_list_env = tmp;
	return (0);
}
