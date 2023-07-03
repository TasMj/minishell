/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:56:18 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/03 18:01:46 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(t_minishell *data)
{
	char	*msg_err;

	if (ft_lstsize(*data->token) == 1)
	{
		if (ft_strcmp((*data->token)->content, "<") == 0
			|| ft_strcmp((*data->token)->content, ">") == 0
			|| ft_strcmp((*data->token)->content, "<<") == 0
			|| ft_strcmp((*data->token)->content, ">>") == 0
			|| ft_strcmp((*data->token)->content, "<>") == 0)
		{
			data->code_err = 2;
			return (err_msg(0, "IGNORE", 2));
		}
		if (ft_strcmp((*data->token)->content, "|") == 0)
		{
			data->code_err = 2;
			msg_err = ft_strjoin("syntax error near unexpected token `", (*data->token)->content);
			msg_err = ft_strjoin_mod(msg_err, "'\n", 1);
			return (err_msg(6, msg_err, 2));
		}
		if (ft_strcmp((*data->token)->content, ":") == 0
			|| ft_strcmp((*data->token)->content, "#") == 0)
			return (0);
		if (ft_strcmp((*data->token)->content, "!") == 0)
		{
			data->code_err = 1;
			return (1);
		}
	}
	if (ft_lstlast(*data->token)->type == APPEND
		|| ft_lstlast(*data->token)->type == HEREDOC
		|| ft_lstlast(*data->token)->type == STDIN
		|| ft_lstlast(*data->token)->type == STDOUT
		|| ft_lstlast(*data->token)->type == PIPE)
		return (err_msg(0, "IGNORE", 2));
	if (ft_strcmp((*data->token)->content, "|") == 0)
	{
		msg_err = ft_strjoin("syntax error near unexpected token `", (*data->token)->content);
		msg_err = ft_strjoin_mod(msg_err, "'\n", 1);
		return (err_msg(6, msg_err, 2));
		// printf("minishell: syntax error near unexpected token `%s'\n", (*data->token)->content);
		return (2);
	}
	return (3);
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
			return (err_msg(1, "IGNORE", 1));
		}
		(*list_token) = (*list_token)->next;
	}
	*list_token = tmp;
	return (0);
}

int	err_redir(t_minishell *data)
{
	t_list	*tmp;
	char	*msg_err;
	
	tmp = *data->token;
	while (*data->token)
	{
		if ((*data->token)->type == WORD)
			(*data->token) = (*data->token)->next;
		else
		{
			if ((*data->token)->type != WORD
				&& (*data->token)->next == NULL)
			{
				data->code_err = 2;
				msg_err = ft_strjoin("syntax error near unexpected token `", (*data->token)->content);
				msg_err = ft_strjoin_mod(msg_err, "'\n", 1);
				return (err_msg(6, msg_err, 2));
			}
			if ((*data->token)->next != NULL && (*data->token)->type != WORD && (*data->token)->next->type != WORD)
			{
				if (((*data->token)->type != PIPE && (*data->token)->next->type == PIPE) 
					|| ((*data->token)->type == PIPE && (*data->token)->next->type != PIPE))
				{
					*data->token = tmp;
					return (1);
				}
				data->code_err = 2;
				msg_err = ft_strjoin("syntax error near unexpected token `", (*data->token)->content);
				msg_err = ft_strjoin_mod(msg_err, "'\n", 1);
				return (err_msg(6, msg_err, 2));
			}
			(*data->token) = (*data->token)->next;
		}
	}
	*data->token = tmp;
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
			if ((*list_token)->quote_trace == 1 || (*list_token)->next->quote_trace == 1)
				(*list_token)->quote_trace = 1;
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
