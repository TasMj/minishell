/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:49:14 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/05 21:14:18 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**ft_copy_list(t_list **copy)
{
	while (*g_list_env)
	{
		add_list(copy, (*g_list_env)->content, 0);
		(*g_list_env) = (*g_list_env)->next;
	}
	return (copy);
}

void	print_list(t_list **list)
{
	t_list	*tmp;

	tmp = (*list);
	while (*list)
	{
		printf("content: [%s], flag_quote: %d\n",
			(*list)->content, (*list)->quote_trace);
		(*list) = (*list)->next;
	}
	(*list) = tmp;
}

/* add to the list, word ready without space. take words with quotes */
void	add_list(t_list **list_token, char *stockage, int flag_space)
{
	t_list	*to_add;

	to_add = ft_lstnew(stockage, flag_space);
	ft_lstadd_back(list_token, to_add);
}
