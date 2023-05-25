/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:04:12 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/25 12:04:54 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

int	set_stdout(t_cmd *cmd, t_list *token)
{
	char	*file;

	file = ft_strdup_size(token->next->content, ft_strlen(token->next->content));
	if (!file)
		return (1);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_out < 0)
		return (1);
	free(file);
	return (0);
}

int	set_stdin(t_cmd *cmd, t_list *token)
{
	char	*file;

	file = ft_strdup_size(token->next->content, ft_strlen(token->next->content));
	if (!file)
		return (1);
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	cmd->fd_in = open(file, O_RDONLY);
	if (cmd->fd_in < 0)
		return (1);
	free(file);
	return (0);
}

int	check_last_file(t_list *token)
{
	t_list	*elem;

	elem = token;
	while (elem && elem->type != PIPE)
	{
		if (elem->type != WORD)
			return (0);
		elem = elem->next;
	}
	return (1);
}

int	set_append(t_cmd *cmd, t_list *token)
{
	char	*file;

	file = ft_strdup_size(token->next->content, ft_strlen(token->next->content));
	if (!file)
		return (1);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	if (check_last_file(token->next) == 1)
		cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		cmd->fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd_out < 0)
		return (1);
	free(file);
	return (0);
}

int	set_fd(t_cmd *cmd, t_list *token)
{
	t_list	*elem;

	elem = token;
	while (elem && elem->type != PIPE)
	{
		if (elem->type == STDOUT)
			set_stdout(cmd, elem);
		else if (elem->type == STDIN)
			set_stdin(cmd, elem);
		else if (elem->type == APPEND)
			set_append(cmd, elem);
		elem = elem->next;
	}
	return (0);
}
