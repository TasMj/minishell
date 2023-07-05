/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:15:49 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/05 17:17:10 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (ft_strcmp((*cmd->cmd)->content, "cd") == 0)
		return (1);
	else if (ft_strcmp((*cmd->cmd)->content, "echo") == 0)
		return (1);
	else if (ft_strcmp((*cmd->cmd)->content, "env") == 0)
		return (1);
	else if (ft_strcmp((*cmd->cmd)->content, "exit") == 0)
		return (1);
	else if (ft_strcmp((*cmd->cmd)->content, "export") == 0)
		return (1);
	else if (ft_strcmp((*cmd->cmd)->content, "pwd") == 0)
		return (1);
	else if (ft_strcmp((*cmd->cmd)->content, "unset") == 0)
		return (1);
	return (0);
}

void	handle_term_sig(int ret)
{
	signal_signal(ret);
	singleton_minishell()->code_err = 128 + WTERMSIG(ret);
	if (singleton_minishell()->code_err == 139)
		put_str_err("Segmentation fault\n");
}

int	open_n_leave(t_list	*token)
{
	int	fd;

	while (token)
	{
		if (token->type == STDOUT)
			fd = open(token->next->content, O_CREAT | O_TRUNC | O_RDWR, 0666);
		else if (token->type == APPEND)
			fd = open(token->next->content, O_CREAT | O_APPEND | O_RDWR, 0666);
		else if (token->type == STDIN)
		{
			fd = open(token->content, O_RDONLY);
			if (fd < 0)
			{
				put_str_err("minishell: ");
				put_str_err(token->next->content);
				put_str_err(": No such file or directory\n");
				return (1);
			}
		}
		close(fd);
		token = token->next;
	}
	return (0);
}
