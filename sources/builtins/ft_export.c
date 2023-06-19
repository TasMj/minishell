/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:11:23 by tas               #+#    #+#             */
/*   Updated: 2023/06/19 16:23:53 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

t_list	**g_list_env;

int	sort_env_ascii(void)
{
	t_list	**copy;

	copy = malloc(sizeof(t_list));
	ft_memset(copy, 0, sizeof(t_list));
	copy = ft_copy_list(copy);
	copy = sort_env(copy);
	print_export(copy);
	free_list(copy);
	return (0);
}

int	add_var_env(char *stock, t_list *tmp)
{
	char	*copy;
	(void)tmp;

	copy = del_equal(stock);
	if (ft_isalpha(copy) == 1)
	{
		free(copy);
		free(stock);
		return (err_msg(5));
	}
	add_list(g_list_env, stock, 0);
	free(copy);
	free(stock);
	
	return (0);
}

int	modify_var(char *stock, t_list *tmp)
{
	char	*copy_env;
	char	*copy_token;

	while (*g_list_env)
	{
		copy_env = del_equal((*g_list_env)->content);
		copy_token = del_equal(stock);
		if (ft_strcmp(copy_env, copy_token) == 1)
			(*g_list_env) = (*g_list_env)->next;
		else if (ft_strcmp(copy_env, copy_token) == 0)
		{
			free((*g_list_env)->content);
			(*g_list_env)->content = ft_strdup(stock);
			*g_list_env = tmp;
			free(copy_env);
			free(copy_token);
			return (1);
		}
		free(copy_env);
		free(copy_token);
	}
	return (0);
}

int	ft_export(t_list **list_token)
{
	t_list	*tmp;
	char	*stock;
	char	*copy;
	
	tmp = *g_list_env;
	if (ft_lstsize(*list_token) == 1)
		sort_env_ascii();
	else
	{
		while (*list_token != NULL)
		{
			if (check_list_equal(list_token) != 1)
				return (0);
			(*list_token) = (*list_token)->next;
			stock = ft_strdup((*list_token)->content);
			(*list_token) = (*list_token)->next;
			while (*list_token && (*list_token)->content[0] != '=' && (*list_token)->flag_space == 0)
			{
				if (*list_token && ft_strlen((*list_token)->content) == 0)
					(*list_token) = (*list_token)->next;
				else
				{
					stock = ft_strjoin_mod(stock, (*list_token)->content, 1);
					(*list_token) = (*list_token)->next;
				}
			}
			copy = del_equal(stock);
			if (is_in_env(copy) == 0)
			{
				free(copy);
				return (add_var_env(stock, tmp));
			}
			else if (modify_var(stock, tmp) == 1)
			{
				free(copy);
				free(stock);
				return (0);
			}
			free(copy);
			free(stock);
			(*list_token) = (*list_token)->next;
		}
	}
	*g_list_env = tmp;
	return (0);
}
