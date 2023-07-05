/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:54:39 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/05 20:55:38 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_min_max(t_list **list, t_min_max *m)
{
	if (ft_strlen_var((*list)->content) >= \
	ft_strlen_var((*list)->next->content))
	{
		m->min = ft_strlen_var((*list)->next->content);
		m->max = ft_strlen_var((*list)->content);
	}
	else
	{
		m->min = ft_strlen_var((*list)->content);
		m->max = ft_strlen_var((*list)->next->content);
	}
}

static int	is_sorted(t_list **list)
{
	t_list		*tmp;
	t_min_max	*m;

	m = malloc(sizeof(t_min_max));
	ft_memset(m, 0, sizeof(t_min_max));
	tmp = *list;
	while ((*list)->next != NULL)
	{
		set_min_max(list, m);
		if (ft_strncmp((*list)->content, (*list)->next->content, m->min) > 0)
		{
			free(m);
			return (1);
		}
		(*list) = (*list)->next;
	}
	free(m);
	*list = tmp;
	return (0);
}

static	void	swap_in_list(t_list **list, t_list *tmp)
{
	char	*tmp_content;

	tmp_content = (*list)->content;
	(*list)->content = (*list)->next->content;
	(*list)->next->content = tmp_content;
	*list = tmp;
}

t_list	**sort_env(t_list **list)
{
	t_list		*tmp;
	t_min_max	*m;

	m = malloc(sizeof(t_min_max));
	ft_memset(m, 0, sizeof(t_min_max));
	tmp = *list;
	while (is_sorted(list) == 1)
	{
		set_min_max(list, m);
		if (ft_strncmp((*list)->content, (*list)->next->content, m->min) > 0)
			swap_in_list(list, tmp);
		(*list) = (*list)->next;
	}
	*list = tmp;
	free(m);
	return (list);
}
