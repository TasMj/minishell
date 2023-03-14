/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:12:00 by tas               #+#    #+#             */
/*   Updated: 2023/03/14 20:14:58 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*dernier;

	if (lst)
	{
		if (*lst)
		{
			dernier = ft_lstlast(*lst);
			dernier->next = new;
		}
		else
			*lst = new;
	}
}

t_list	*ft_lstnew(char *input)
{
	t_list *new;
	
	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = input;
	// printf("content: [%s]\n", new->content);
	new->next = NULL;
    return (new);
}

void	print_list(t_list **list)
{
	t_list *tmp;
	int i;

	i = 0;
	tmp = (*list);
	while (*list)
	{
		printf("****ID Token****\n");
		printf("content: [%s]\n", (*list)->content);
		printf("type: [%d]\n", (*list)->type);
		printf("****************\n");
		(*list) = (*list)->next;
	}
	(*list) = tmp;
}