/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:49:14 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/10 22:06:28 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**ft_copy_list(t_list **copy, t_minishell *data)
{
	while (*data->env)
	{
		add_list(copy, (*data->env)->content, 0);
		(*data->env) = (*data->env)->next;
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

void	reunite_token(t_list **lst)
{
	t_list	*tmp;
	t_list	*next_token;

	tmp = *lst;
	while (*lst && (*lst)->next)
	{
		if (is_redir((*lst)->content) == 1)
			(*lst) = (*lst)->next;
		else if (((*lst)->next->flag_space == 0
				&& is_redir((*lst)->next->content) == 0))
		{
			next_token = (*lst)->next;
			(*lst)->content = ft_strjoin_mod((*lst)->content, \
			next_token->content, 1);
			if ((*lst)->quote_trace == 1 || (*lst)->next->quote_trace == 1)
				(*lst)->quote_trace = 1;
			(*lst)->flag_space = next_token->flag_space;
			(*lst)->next = next_token->next;
			free(next_token->content);
			free(next_token);
		}
		else
			(*lst) = (*lst)->next;
	}
	*lst = tmp;
}
