/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:33:10 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/05 22:27:34 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_list(t_list **list)
{
	t_list	*to_free;
	t_list	*iter;

	if (*list)
	{
		iter = *list;
		while (iter)
		{
			to_free = iter;
			iter = iter->next;
			free(to_free);
		}
		*list = NULL;
	}
	free(list);
}

void	free_all(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

int	free_and_ret(char *s1, char *s2, int ret)
{
	free(s1);
	free(s2);
	return (ret);
}
