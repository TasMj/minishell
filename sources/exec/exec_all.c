/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:01:28 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/25 12:33:54 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

// Converti les tokens d'une list en char **
char	**lst_to_tab(t_list **lst)
{
	t_list	*elem;
	char	**tab;
	int	i;

	elem = *lst;
	tab = malloc(sizeof(char *) * ft_lstsize(*lst));
	if (!tab)
		return (NULL);
	i = 0;
	while (elem)
	{
		tab[i] = ft_strdup_size(elem->content, ft_strlen(elem->content));
		elem = elem->next;
		i++;
	}
	tab[i] = 0;
	return (tab);
}

// Exec la commande cmd avec ses fd d'entree et sortie assignes
int	exec_cmd(t_cmd *cmd, t_exec *data)
{
	char	**tab;

	tab = lst_to_tab(cmd->cmd);
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (1);
	if (cmd->pid == 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		if (data->nb_pipes > 0)
			close_all(data, data->nb_pipes - 1);
		if (exec_builtin(cmd->cmd) == 1)
			return (0);
		execve(cmd->path, tab, data->env);
		free_tab(tab);
	}
	return (0);
}

int	check_op(t_cmd *cmd)
{
	t_list	*elem;

	elem = *cmd->cmd;
	while (elem)
	{
		if (elem->type != WORD && elem->type != PIPE)
			return (1);
		elem = elem->next;
	}
	return (0);
}

int	exec_global(t_exec *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd)
	{
		if (check_op(&(data->cmd[i])) == 1)
			exec_op(&(data->cmd[i]), data);
		if (!(check_op(&(data->cmd[i])) == 1 && data->nb_pipes == 0))
			exec_cmd(&(data->cmd[i]), data);
		if (i != data->nb_pipes)
			close(data->cmd[i].fd_out);
		waitpid(data->cmd[i].pid, NULL, 0);
		i++;
	}
	return (0);
}
