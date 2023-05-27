/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:11:23 by tas               #+#    #+#             */
/*   Updated: 2023/05/27 17:25:15 by tmejri           ###   ########.fr       */
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

int	add_var_env(t_list **token, t_list *tmp)
{
	char	*add_env;
	char	*copy;

	add_env = ft_strdup_size((*token)->content, ft_strlen((*token)->content));
	while ((*token)->next != NULL && (*token)->next->flag_space != 1)
	{
		(*token) = (*token)->next;
		add_env = ft_strjoin_mod(add_env, (*token)->content, 0);
	}
	copy = ft_strdup(add_env);
	if (ft_isalpha(take_off_equal(copy)) == 1)
	{
		// free(add_env);
		free(copy);
		return (err_msg(5));
	}
	add_list(g_list_env, add_env, 0);
	*g_list_env = tmp;
	free(copy);
	// free(add_env);
	return (0);
}

int	modify_var(t_list **token, t_list *tmp)
{
	char	*copy_env;
	char	*copy_token;

	while (*g_list_env)
	{
		copy_env = ft_strdup((*g_list_env)->content);
		copy_token = ft_strdup((*token)->content);
		if (ft_strcmp(take_off_equal(copy_env), take_off_equal(copy_token)) == 1)
		{
			free(copy_env);
			(*g_list_env) = (*g_list_env)->next;
		}
		else if (ft_strcmp(take_off_equal(copy_env), take_off_equal(copy_token)) == 0)
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
			free(copy_token);
			free(copy_env);
			return (1);
		}
	}
	free(copy_token);
	return (0);
}

int	ft_export(t_list **list_token)
{
	t_list	*tmp;
	char	*copy;

	tmp = *g_list_env;
	if (ft_lstsize(*list_token) == 1)
		sort_env_ascii();
	else
	{
		while (*list_token != NULL)
		{
			(*list_token) = (*list_token)->next;
			copy = ft_strdup((*list_token)->content);
			if (check_equal((*list_token)->content) == 1)
			{
				if (is_in_env(take_off_equal(copy)) == 0)
					return (add_var_env(list_token, tmp));
				else if (modify_var(list_token, tmp) == 1)
				{
					free(copy);
					return (0);
				}
			}
			free(copy);
			(*list_token) = (*list_token)->next;
		}
	}
	*g_list_env = tmp;
	return (0);
}
