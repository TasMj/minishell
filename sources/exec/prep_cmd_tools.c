/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_cmd_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:56:30 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/05 17:57:28 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_lst_type(t_list **list_token, t_list *elem)
{
	t_list	*to_add;

	to_add = ft_lstnew(elem->content, elem->flag_space);
	to_add->type = elem->type;
	to_add->quote_trace = elem->quote_trace;
	ft_lstadd_back(list_token, to_add);
}

int	set_prep_tools(t_minishell *data)
{
	data->x->cmd = malloc(sizeof(t_cmd) * data->x->nb_cmd);
	if (!data->x->cmd)
		return (1);
	set_to_zero(data->x);
	return (0);
}

int	cmd_access(t_cmd *cmd, char *msg_err)
{
	if (access((*cmd->cmd)->content, F_OK) == -1)
	{
		msg_err = ft_strjoin((*cmd->cmd)->content,
				": No such file or directory\n");
		err_write(msg_err, 2);
		cmd->data->code_err = 127;
		return (free(msg_err), 1);
	}
	else if (access((*cmd->cmd)->content, X_OK) == -1)
	{
		(void)msg_err;
		put_str_err("minishell: ");
		put_str_err((*cmd->cmd)->content);
		put_str_err(": Permission denied\n");
		cmd->data->code_err = 126;
		return (1);
	}
	else if (is_dir((*cmd->cmd)->content) == 1)
	{
		msg_err = ft_strjoin((*cmd->cmd)->content, ": Is a directory\n");
		err_write(msg_err, 2);
		cmd->data->code_err = 126;
		return (free(msg_err), 1);
	}
	return (0);
}
