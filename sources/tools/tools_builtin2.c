/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_builtin2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:41:38 by tmejri            #+#    #+#             */
/*   Updated: 2023/05/27 16:46:57 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"
/* export =*/

/* return size of str until '=' */
int	ft_strlen_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] && i != '=')
		i++;
	return (i);
}

void	print_export(t_list **list)
{
	t_list	*tmp;

	tmp = (*list);
	while (*list)
	{
		printf("export %s\n", (*list)->content);
		(*list) = (*list)->next;
	}
	(*list) = tmp;
}

void	set_min_max(t_list **list, t_min_max *m)
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

int	is_sorted(t_list **list)
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
			return (1);
		(*list) = (*list)->next;
	}
	*list = tmp;
	return (0);
}

void	swap_in_list(t_list **list, t_list *tmp, char *tmp1, char *tmp2)
{
	tmp1 = ft_strdup_size((*list)->content, ft_strlen((*list)->content));
	tmp2 = ft_strdup_size((*list)->next->content, \
	ft_strlen((*list)->next->content));
	(*list)->content = ft_strdup_size(tmp2, ft_strlen(tmp2));
	(*list)->next->content = ft_strdup_size(tmp1, ft_strlen(tmp1));
	free(tmp1);
	free(tmp2);
	*list = tmp;
}

t_list	**sort_env(t_list **list)
{
	t_list		*tmp;
	char		*tmp1;
	char		*tmp2;
	t_min_max	*m;

	m = malloc(sizeof(t_min_max));
	ft_memset(m, 0, sizeof(t_min_max));
	tmp = *list;
	tmp1 = NULL;
	tmp2 = NULL;
	while (is_sorted(list) == 1)
	{
		set_min_max(list, m);
		if (ft_strncmp((*list)->content, (*list)->next->content, m->min) > 0)
			swap_in_list(list, tmp, tmp1, tmp2);
		(*list) = (*list)->next;
	}
	*list = tmp;
	return (list);
}

int	ft_isalpha(char *str)
{
	int i;
	
	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))
			i++;
		else
			return (1);
	}
	return (0);
}