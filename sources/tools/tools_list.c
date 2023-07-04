/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:12:00 by tas               #+#    #+#             */
/*   Updated: 2023/07/04 11:25:12 by jthuysba         ###   ########.fr       */
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

t_list	*ft_lstnew(char *input, int flag_space)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	ft_memset(new, 0, sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = input;
	new->flag_space = flag_space;
	if (input[0] == 34 || input[0] == 39)
		new->quote_trace = 1;
	new->next = NULL;
	return (new);
}

void	print_list(t_list **list)
{
	t_list	*tmp;

	tmp = (*list);
	while (*list)
	{
		printf("content: [%s], flag_quote: %d\n", (*list)->content, (*list)->quote_trace);
		(*list) = (*list)->next;
	}
	(*list) = tmp;
}

/* add to the list, word ready without space. take words with quotes */
void	add_list(t_list **list_token, char *stockage, int flag_space)
{
	t_list	*to_add;

	// printf("1 : %p\n", to_add->content);
	to_add = ft_lstnew(stockage, flag_space);
	ft_lstadd_back(list_token, to_add);
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
