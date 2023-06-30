/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_builtin2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:41:38 by tmejri            #+#    #+#             */
/*   Updated: 2023/06/27 18:18:47 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* return size of str until '=' */
static int	ft_strlen_var(char *str)
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

static void swap_in_list(t_list **list, t_list *tmp)
{
    char *tmp_content;
	
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

int	ft_isalpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= 'a' && str[i] <= 'z'))
			i++;
		else
		{
			printf("minishell: export: `%s': not a valid identifier\n", str);
			return (1);
		}
	}
	return (0);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '+' || str[i] == '-'))
			return (0);
		i++;
	}
	return (1);
}
