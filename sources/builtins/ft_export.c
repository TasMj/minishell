/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:11:23 by tas               #+#    #+#             */
/*   Updated: 2023/05/25 14:18:09 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

t_list	**list_ENVI;

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
	add_list(list_ENVI, add_env, 0);
	*list_ENVI = tmp;
	return (0);
}

int	modify_var(t_list **token, t_list *tmp)
{
	while (*list_ENVI)
	{
		if (ft_strcmp(take_off_equal((*list_ENVI)->content), \
		take_off_equal((*token)->content)) == 1)
			(*list_ENVI) = (*list_ENVI)->next;
		else if (ft_strcmp(take_off_equal((*list_ENVI)->content), \
		take_off_equal((*token)->content)) == 0)
		{
			(*list_ENVI)->content = ft_strdup_size((*token)->content, \
			ft_strlen((*token)->content));
			while ((*token)->next != NULL && (*token)->next->flag_space != 1)
			{
				(*token) = (*token)->next;
				(*list_ENVI)->content = ft_strjoin_mod((*list_ENVI)->content, \
				(*token)->content, 0);
			}
			*list_ENVI = tmp;
			return (1);
		}
	}
	return (0);
}

int	ft_export(t_list **list_token)
{
	t_list	*tmp;

	tmp = *list_ENVI;
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
	*list_ENVI = tmp;
	return (0);
}
