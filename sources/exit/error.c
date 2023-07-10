/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:28:23 by tas               #+#    #+#             */
/*   Updated: 2023/07/10 22:05:33 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_main_tools(t_minishell *data)
{
	free_list_token_content(data->token);
	free_list(data->token);
	free(data->input);
}

int	err_msg(int n, char *msg_err, int code_err)
{
	if (n != 6)
		(void)msg_err;
	if (n == 0)
		err_write(ERR_REDIR_IN_OUT, code_err);
	else if (n == 1)
		err_write(ERR_QUOTE, code_err);
	else if (n == 3)
		err_write(ERR_MANY_ARG, code_err);
	else if (n == 4)
		err_write(ERR_HOME, code_err);
	else if (n == 5)
		err_write(ERR_EXPORT, code_err);
	else if (n == 6)
	{
		err_write(msg_err, code_err);
		free(msg_err);
	}
	return (1);
}

void	free_end(t_minishell *data)
{
	free_list_token_content(data->token);
	free_list(data->token);
	free(data->input);
	free_list_token_content(data->env);
	free_list(data->env);
}

void	free_list_token_content(t_list **list_token)
{
	t_list	*tmp;

	if (!list_token)
		return ;
	tmp = (*list_token);
	while (tmp)
	{
		if (tmp->content)
		{
			if (tmp->content != NULL)
				free(tmp->content);
		}
		tmp = tmp->next;
	}
}
