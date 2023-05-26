/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:11:23 by tas               #+#    #+#             */
/*   Updated: 2023/05/26 17:37:22 by tmejri           ###   ########.fr       */
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
	return (0);
}

int	add_var_env(t_list **token, t_list *tmp)
{
	char	*add_env;

	add_env = ft_strdup_size((*token)->content, ft_strlen((*token)->content));
	while ((*token)->next != NULL && (*token)->next->flag_space != 1)
	{
		(*token) = (*token)->next;
		add_env = ft_strjoin_mod(add_env, (*token)->content, 0);
	}
	if (ft_isalpha(take_off_equal(add_env)) == 0)
		return (err_msg(5));
	add_list(g_list_env, add_env, 0);
	*g_list_env = tmp;
	return (0);
}

int	modify_var(t_list **token, t_list *tmp)
{
	while (*g_list_env)
	{
		if (ft_strcmp(take_off_equal((*g_list_env)->content), \
		take_off_equal((*token)->content)) == 1)
			(*g_list_env) = (*g_list_env)->next;
		else if (ft_strcmp(take_off_equal((*g_list_env)->content), \
		take_off_equal((*token)->content)) == 0)
		{
			(*g_list_env)->content = ft_strdup_size((*token)->content, \
			ft_strlen((*token)->content));
			while ((*token)->next != NULL && (*token)->next->flag_space != 1)
			{
				(*token) = (*token)->next;
				(*g_list_env)->content = ft_strjoin_mod((*g_list_env)->content, \
				(*token)->content, 0);
			}
			*g_list_env = tmp;
			return (1);
		}
	}
	return (0);
}

int	ft_export(t_list **list_token)
{
	t_list	*tmp;

	tmp = *g_list_env;
	if (ft_lstsize(*list_token) == 1)
		sort_env_ascii();
	else
	{
		while (*list_token != NULL)
		{
			(*list_token) = (*list_token)->next;
			if (check_equal((*list_token)->content) == 1)
			{
				if (is_in_env(take_off_equal((*list_token)->content)) == 0)
					return (add_var_env(list_token, tmp));
				else
				{
					if (modify_var(list_token, tmp) == 1)
						return (0);
				}
			}
			(*list_token) = (*list_token)->next;
		}
	}
	*g_list_env = tmp;
	return (0);
}
