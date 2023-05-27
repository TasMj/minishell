/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:11:23 by tas               #+#    #+#             */
/*   Updated: 2023/05/28 00:41:47 by tmejri           ###   ########.fr       */
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
	char	*add_env;
	char	*copy;
	(void)tmp;

	add_env = ft_strdup(stock);
	copy = ft_strdup(add_env);
	if (ft_isalpha(del_equal(copy)) == 1)
	{
		free(copy);
		return (err_msg(5));
	}
	add_list(g_list_env, add_env, 0);
	free(copy);
	return (0);
}

void	modif(char *copy_token, char *copy_env, t_list *tmp)
{
	(*g_list_env)->content = ft_strdup(copy_token);
	*g_list_env = tmp;
	free(copy_token);
	free(copy_env);
}

int	modify_var(char *stock, t_list *tmp)
{
	char	*copy_env;
	char	*copy_token;

	while (*g_list_env)
	{
		copy_env = ft_strdup((*g_list_env)->content);
		copy_token = ft_strdup(stock);
		if (ft_strcmp(del_equal(copy_env), del_equal(copy_token)) == 1)
		{
			free(copy_env);
			(*g_list_env) = (*g_list_env)->next;
		}
		else if (ft_strcmp(del_equal(copy_env), del_equal(copy_token)) == 0)
		{
			modif(copy_token, copy_env, tmp);
			return (1);
		}
	}
	free(copy_token);
	return (0);
}

int	ft_export(t_list **list_token)
{
	t_list	*tmp;
	char	*stock;
	
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
						stock = ft_strjoin(stock, (*list_token)->content);
						(*list_token) = (*list_token)->next;
					}
				}
				if (is_in_env(del_equal(stock)) == 0)
					return (add_var_env(stock, tmp));
				else if (modify_var(stock, tmp) == 1)
					return (0);
			(*list_token) = (*list_token)->next;
		}
	}
	*g_list_env = tmp;
	return (0);
}
