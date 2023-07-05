/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:41:06 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/05 23:46:48 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(t_minishell *data)
{
	char	*msg_err;

	if (ft_lstlast(*data->token)->type == APPEND
		|| ft_lstlast(*data->token)->type == HEREDOC
		|| ft_lstlast(*data->token)->type == STDIN
		|| ft_lstlast(*data->token)->type == STDOUT
		|| ft_lstlast(*data->token)->type == PIPE)
		return (err_msg(0, "IGNORE", 2));
	if (ft_strcmp((*data->token)->content, "|") == 0)
	{
		msg_err = ft_strjoin("syntax error near unexpected token `", \
			(*data->token)->content);
		msg_err = ft_strjoin_mod(msg_err, "'\n", 1);
		return (err_msg(6, msg_err, 2));
		return (2);
	}
	return (3);
}

int	err_quote(t_list **lst, t_minishell *data)
{
	t_list	*tmp;

	tmp = *lst;
	while (*lst)
	{
		if (check_pair_quote((*lst)->content) == 1)
		{
			*lst = tmp;
			return (err_msg(1, "IGNORE", 1));
		}
		(*lst) = (*lst)->next;
	}
	*lst = tmp;
	if (ft_lstsize(*lst) == 1 && (ft_strcmp((*lst)->content, "\'\'") == 0
			|| ft_strcmp((*lst)->content, "\"\"") == 0))
	{
		data->code_err = 127;
		put_str_err("minishell: : command not found\n");
		return (1);
	}
	return (0);
}
