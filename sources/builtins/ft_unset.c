/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:11:35 by tas               #+#    #+#             */
/*   Updated: 2023/06/19 16:36:54 by tmejri           ###   ########.fr       */
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
	char	*var;
	
	tmp = *g_list_env;
	while (*g_list_env)
	{
		var = var_name((*g_list_env)->content);
		if (ft_strcmp(var, str) == 0)
		{
			*g_list_env = tmp;
			free(var);
			return (1);
		}
		free(var);
		(*g_list_env) = (*g_list_env)->next;
	}
	*g_list_env = tmp;
	return (0);
}

void	del(char *str)
{
	t_list	*tmp_first;
	t_list	*tmp_next;
	t_list	*var_before;
	char	*var;

	var = var_name((*g_list_env)->content);
	if (ft_strcmp(var, str) == 0)
		tmp_first = (*g_list_env)->next;
	else
	{
		tmp_first = *g_list_env;
		while ((*g_list_env)->next != NULL && ft_strcmp(var, str) == 1)
		{
			var_before = (*g_list_env);
			(*g_list_env) = (*g_list_env)->next;
			free(var);
			var = var_name((*g_list_env)->content);
		}
		(*g_list_env) = var_before;
		if ((*g_list_env)->next->next != NULL)
			tmp_next = (*g_list_env)->next->next;
		else
			tmp_next = NULL;
		(*g_list_env)->next = tmp_next;
	}
	*g_list_env = tmp_first;
	free(var);
}

int	ft_unset(t_list **list_token)
{
	(*list_token) = (*list_token)->next;
	while (*list_token != NULL)
	{
		if (check_var((*list_token)->content) == 1)
			del((*list_token)->content);
		(*list_token) = (*list_token)->next;
	}
	return (0);
}
