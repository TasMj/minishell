/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:56:18 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/05 22:42:26 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	list_one_tok_bis(t_minishell *data)
{
	char	*msg_err;

	if (ft_strcmp((*data->token)->content, "<") == 0
		|| ft_strcmp((*data->token)->content, ">") == 0
		|| ft_strcmp((*data->token)->content, "<<") == 0
		|| ft_strcmp((*data->token)->content, ">>") == 0
		|| ft_strcmp((*data->token)->content, "<>") == 0)
	{
		data->code_err = 2;
		return (err_msg(0, "IGNORE", 2));
	}
	else if (ft_strcmp((*data->token)->content, "|") == 0)
	{
		data->code_err = 2;
		msg_err = ft_strjoin("syntax error near unexpected token `", \
		(*data->token)->content);
		msg_err = ft_strjoin_mod(msg_err, "'\n", 1);
		return (err_msg(6, msg_err, 2));
	}
	else if (ft_strcmp((*data->token)->content, "!") == 0)
	{
		data->code_err = 1;
		return (1);
	}
	return (0);
}

int	list_one_tok(t_minishell *data)
{
	if (ft_lstsize(*data->token) == 1)
	{
		if (list_one_tok_bis(data) == 1)
			return (1);
		else if (ft_strcmp((*data->token)->content, ":") == 0
			|| ft_strcmp((*data->token)->content, "#") == 0)
			return (0);
	}
	return (3);
}

int	print_err_syntax(t_minishell *data, t_list *tmp)
{
	char	*msg_err;

	data->code_err = 2;
	msg_err = ft_strjoin("syntax error near unexpected token `", \
	(*data->token)->content);
	msg_err = ft_strjoin_mod(msg_err, "'\n", 1);
	*data->token = tmp;
	return (err_msg(6, msg_err, 2));
}

int	handl_syntax_err(t_minishell *data, t_list *tmp)
{
	if (((*data->token)->type != PIPE && (*data->token)->next->type == PIPE)
		|| ((*data->token)->type == PIPE && (*data->token)->next->type != PIPE))
	{
		*data->token = tmp;
		return (3);
	}
	return (print_err_syntax(data, tmp));
}

int	err_redir(t_minishell *data)
{
	t_list	*tmp;

	tmp = *data->token;
	if (list_one_tok(data) != 3)
		return (1);
	while (*data->token)
	{
		if ((*data->token)->type == WORD)
			(*data->token) = (*data->token)->next;
		else
		{
			if ((*data->token)->type != WORD && (*data->token)->next == NULL)
				return (print_err_syntax(data, tmp));
			if ((*data->token)->next != NULL && (*data->token)->type != WORD
				&& (*data->token)->next->type != WORD)
				return (handl_syntax_err(data, tmp));
			(*data->token) = (*data->token)->next;
		}
	}
	*data->token = tmp;
	return (3);
}
