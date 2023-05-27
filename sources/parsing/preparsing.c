/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:56:18 by tmejri            #+#    #+#             */
/*   Updated: 2023/05/27 13:06:41 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

int	syntax_error(t_list **list_token)
{
	if (!list_token || ft_lstsize(*list_token) == 0)
		return (0);
	if (ft_lstsize(*list_token) == 1)
	{
		if (ft_strcmp((*list_token)->content, "<") == 0
			|| ft_strcmp((*list_token)->content, ">") == 0
			|| ft_strcmp((*list_token)->content, "<<") == 0
			|| ft_strcmp((*list_token)->content, ">>") == 0
			|| ft_strcmp((*list_token)->content, "<>") == 0)
			return (err_msg(0));
	}
	if (ft_lstlast(*list_token)->type == APPEND
		|| ft_lstlast(*list_token)->type == HEREDOC
		|| ft_lstlast(*list_token)->type == STDIN
		|| ft_lstlast(*list_token)->type == STDOUT
		|| ft_lstlast(*list_token)->type == PIPE)
		return (err_msg(0));
	return (2);
}

int	err_quote(t_list **list_token)
{
	t_list	*tmp;

	tmp = *list_token;
	while (*list_token)
	{
		if (check_pair_quote((*list_token)->content) == 1)
		{
			*list_token = tmp;
			return (err_msg(1));
		}
		(*list_token) = (*list_token)->next;
	}
	*list_token = tmp;
	return (0);
}
