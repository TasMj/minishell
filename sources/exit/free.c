/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:33:10 by tmejri            #+#    #+#             */
/*   Updated: 2023/03/07 14:20:53 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_list **list)
{
	t_list	*to_free;
	t_list	*iter;

	iter = *list;
	while (iter)
	{
		to_free = iter;
		iter = iter->next;
		free(to_free);
	}
	*list = NULL;
	free(list);
}

void	free_all(char *s1, char *s2)
{
	free(s1);
	free(s2);
}