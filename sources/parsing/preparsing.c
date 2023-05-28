/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:56:18 by tmejri            #+#    #+#             */
/*   Updated: 2023/05/28 16:41:21 by tmejri           ###   ########.fr       */
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

void    reunite_token(t_list **list_token)
{
    t_list  *tmp;
    
    tmp = *list_token;
    while (*list_token && (*list_token)->next)
    {
        if ((*list_token)->next->flag_space == 0)
        {
            (*list_token)->content = ft_strjoin_mod((*list_token)->content, (*list_token)->next->content, 3);
            (*list_token)->flag_space = (*list_token)->next->flag_space;
            (*list_token)->next = (*list_token)->next->next;
        }
        else
            (*list_token) = (*list_token)->next;
    }
    *list_token = tmp;
}
