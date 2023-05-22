/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:10:25 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/22 16:29:00 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

t_list	**get_trunc_cmd(t_list *tok)
{
	t_list	**lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	*lst = NULL;
	while (tok && tok->type == WORD)
	{
		add_list(lst, tok->content, tok->flag_space);
		tok = tok->next;
	}
	get_type(lst);
	return (lst);
}

char	*get_file(t_list *lst)
{
	return (ft_lstlast(lst)->content);
}

int	get_op_type(t_list *lst)
{
	while (lst->next != ft_lstlast(lst) && lst->next)
		lst = lst->next;
	return (lst->type);
}

int	exec_stdout(t_list *cmd, t_exec *data, char *file)
{
	int		fd;
	pid_t		pid;
	char		**tab;
	
	tab = lst_to_tab(&cmd);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		dup2(fd, STDOUT_FILENO);
		execve(find_path(data->env, cmd->content), tab, data->env);
		close(fd);
	}
	waitpid(pid, NULL, 0);
	close(fd);
	free_tab(tab);
	return (0);
}

int	exec_redirect(t_list *cmd, int type, char *file, t_exec *data)
{
	if (type == STDOUT)
		exec_stdout(cmd, data, file);
	else if (type == STDIN)
	{
		printf("stdin\n");
	}
	else if (type == APPEND)
	{
		printf("append\n");
	}
	else if (type == HEREDOC)
	{
		printf("heredoc\n");
	}
	return (0);
}

int	exec_op(t_cmd *cmd, t_exec *data)
{
	(void) data;
	
	t_list	**trunc_cmd;
	t_list	*elem;
	char	*file;
	int	fd;
	int	type;

	trunc_cmd = get_trunc_cmd(*cmd->cmd);
	file = get_file(*cmd->cmd);
	type = get_op_type(*cmd->cmd);
	elem = *cmd->cmd;
	while (elem)
	{
		if (elem->type != WORD && elem->next)
		{
			fd = open(elem->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				return (1);
			close(fd);
		}
		elem = elem->next;
	}

	exec_redirect(*trunc_cmd, type, file, data);
	
	free(file);
	free_list(trunc_cmd);
	return (0);
}
