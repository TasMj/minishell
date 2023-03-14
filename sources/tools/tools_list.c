/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:12:00 by tas               #+#    #+#             */
/*   Updated: 2023/03/14 00:42:41 by tas              ###   ########.fr       */
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
	printf("content: [%s]\n", new->content);
	new->next = NULL;
    return (new);
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

void    print_list(t_list **list_token)
{
    while((*list_token)->next != NULL)
    {
        printf("print: %s\n", (*list_token)->content);
        (*list_token) = (*list_token)->next;
    }
}

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst && f)
	{
		while (lst)
		{
			f(lst->content);
			lst = lst->next;
		}
	}
}

// void del(t_list **lst, t_list *elem)
// {
//     t_list *prev;

//     if (!*lst || !elem)
//         return;
//     if (*lst == elem)
//     {
//         *lst = elem->next;
//         free(elem);
//         return;
//     }
//     prev = *lst;
//     while (prev->next && prev->next != elem)
//         prev = prev->next;
//     if (prev->next == elem)
//     {
//         prev->next = elem->next;
//         free(elem);
//     }
// }

// void	ft_lstdelone(t_list **list, t_list *lst, void (*del)(t_list **, t_list *))
// {
// 	if (lst && del)
// 	{
// 		(*del)(list, lst->content);
// 		free(lst);
// 	}
// }