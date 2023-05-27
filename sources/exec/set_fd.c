/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:04:12 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/27 22:58:44 by jthuysba         ###   ########.fr       */
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

int file_exists(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file != NULL)
	{
        // Le fichier existe
        fclose(file); // Ferme le fichier
        return (1);
    }
	else
	{
        // Le fichier n'existe pas
        return (0);
    }
}

int	set_stdin(t_cmd *cmd, t_list *token)
{
	char	*file;

	file = ft_strdup_size(token->next->content, ft_strlen(token->next->content));
	if (!file)
		return (1);
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (file_exists(file) == 0)
	{
		free(file);
		return (err_msg());
	}
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

t_list	**get_heredoc_cmd(t_cmd *cmd, t_list *token)
{
	t_list	**lst;
	t_list	*elem;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	*lst = NULL;
	elem = *cmd->cmd;
	while (elem)
	{
		add_list(lst, elem->content, elem->flag_space);
		elem = elem->next;
	}
	elem = token;
	add_list(lst, elem->content, elem->flag_space);
	elem = elem->next;
	add_list(lst, elem->content, elem->flag_space);
	get_type(lst);
	return (lst);
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
		else if (elem->type == HEREDOC)
			cmd->cmd = get_heredoc_cmd(cmd, elem);
		elem = elem->next;
	}
	return (0);
}
