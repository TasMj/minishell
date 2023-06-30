/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:56:18 by tmejri            #+#    #+#             */
/*   Updated: 2023/06/30 19:44:58 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(t_list **list_token)
{
	if (ft_lstsize(*list_token) == 1)
	{
		if (ft_strcmp((*list_token)->content, "<") == 0
			|| ft_strcmp((*list_token)->content, ">") == 0
			|| ft_strcmp((*list_token)->content, "<<") == 0
			|| ft_strcmp((*list_token)->content, ">>") == 0
			|| ft_strcmp((*list_token)->content, "<>") == 0)
			return (err_msg(0));
		if (ft_strcmp((*list_token)->content, "|") == 0)
		{
			printf("minishell: syntax error near unexpected token `%s'\n", (*list_token)->content);
			return (0);
		}
		if (ft_strcmp((*list_token)->content, ":") == 0
			|| ft_strcmp((*list_token)->content, "!") == 0)
			return (0);
	}
	if (ft_lstlast(*list_token)->type == APPEND
		|| ft_lstlast(*list_token)->type == HEREDOC
		|| ft_lstlast(*list_token)->type == STDIN
		|| ft_lstlast(*list_token)->type == STDOUT
		|| ft_lstlast(*list_token)->type == PIPE)
		return (err_msg(0));
	if (ft_strcmp((*list_token)->content, "|") == 0)
	{
		printf("minishell: syntax error near unexpected token `%s'\n", (*list_token)->content);
		return (0);
	}
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

int	err_redir(t_list **list_token)
{
	t_list	*tmp;

	tmp = *list_token;
	while (*list_token)
	{
		if ((*list_token)->type == WORD)
			(*list_token) = (*list_token)->next;
		else
		{
			if ((*list_token)->next != NULL && (*list_token)->type != WORD && (*list_token)->next->type != WORD)
			{
				// printf("minishell: syntax error near unexpected token `%s'\n", (*list_token)->next->content);
				err_write("syntax error near unexpected token ");
				write(2, &(*list_token)->next->content, ft_strlen((*list_token)->next->content));
				write(2, "\n", 1);
				return (1);
			}
			(*list_token) = (*list_token)->next;
		}
	}
	*list_token = tmp;
	return (3);
}

void reunite_token(t_list **list_token)
{
    t_list *tmp;
	
    tmp = *list_token;
    while (*list_token && (*list_token)->next)
    {
		if (is_redir((*list_token)->content) == 1)
            (*list_token) = (*list_token)->next;
        else if (((*list_token)->next->flag_space == 0 && is_redir((*list_token)->next->content) == 0))
        {
            t_list *next_token = (*list_token)->next;
            (*list_token)->content = ft_strjoin_mod((*list_token)->content, next_token->content, 1);
            (*list_token)->flag_space = next_token->flag_space;
            (*list_token)->next = next_token->next;
            free(next_token->content);
            free(next_token);
        }
        else
            (*list_token) = (*list_token)->next;
    }
    *list_token = tmp;
}
