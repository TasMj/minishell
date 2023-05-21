/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:01:28 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/21 22:40:42 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

char	**lst_to_tab(t_list **lst)
{
	char	**tab;
	int	i;

	tab = malloc(sizeof(char *) * ft_lstsize(*lst));
	if (!tab)
		return (NULL);
	i = 0;
	while (*lst)
	{
		tab[i] = ft_strdup_size((*lst)->content, ft_strlen((*lst)->content));
		*lst = (*lst)->next;
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
		execve(cmd->path, tab, data->env);
		free_tab(tab);
		// exec(cmd, data);
	}
	return (0);
}

// int	exec_type(t_cmd *cmd, t_exec *data)
// {
// 	if (cmd->type == WORD)
// 		exec_cmd(cmd, data);
// 	else if (cmd->type == STDIN)
// 		exec_stdin(cmd, data);
// 	else if (cmd->type == STDOUT || cmd->type == APPEND)
// 		exec_stdout(cmd, data);
// 	else if (cmd->type == HEREDOC)
// 		heredoc(data->token, data->env);
// 	return (0);
// }

int	exec_global(t_exec *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmd)
	{
		exec_cmd(&(data->cmd[i]), data);
		// exec_type(&(data->cmd[i]), data)
		
		if (i != data->nb_pipes)
			close(data->cmd[i].fd_out);
		waitpid(data->cmd[i].pid, NULL, 0);
		i++;
	}
	return (0);
}

int	exec_all(t_list *token, char **env)
{
	t_exec	data;

	data.token = &token;
	data.env = env;
	setup_pipes(&data);
	setup_cmd(&data);
	if (exec_global(&data) == 1)
	{
		clean_all(&data);
		return (1);
	}
	clean_all(&data);
	return (0);
}
