/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cmd_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:57:06 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/16 13:25:33 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Retourne le nombre de token avant l'operateur
int	cmd_size(t_list *token)
{
	int	count;
	
	count = 0;
	while (token && token->type == WORD)
	{
		count++;
		token = token->next;
	}
	return (count);
}

// Retourne la commande avec les args jusquau premier operateur
char	**get_cmd(t_list *token)
{
	char		**cmd;
	int		i;

	cmd = malloc(sizeof(char *) * (cmd_size(token) + 1));
	i = 0;
	while (token && token->type == WORD)
	{
		cmd[i] = ft_strdup_size(token->content, ft_strlen(token->content));
		i++;
		token = token->next;
	}
	cmd[i] = 0;
	return (cmd);
}

// Setup fd in et out pour chaque commande
void	set_fd(t_cmd *cmd, t_exec *data)
{
	if (cmd->id == 0)
	{
		cmd->fd_in = STDIN_FILENO;
		cmd->fd_out = data->fd[0][1];	
	}
	else if (cmd->id == data->nb_pipes)
	{
		cmd->fd_in = data->fd[cmd->id - 1][0];
		cmd->fd_out = STDOUT_FILENO;
	}
	else
	{
		cmd->fd_in = data->fd[cmd->id - 1][0];
		cmd->fd_out = data->fd[cmd->id][1];
	}
}

// Setup chaque commande dans une struct cmd
void	setup_cmd(t_exec *data)
{
	int	i;
	t_list	*token;
	t_path	p;

	token = *(data->token);
	data->cmd = malloc(sizeof(t_cmd) * nb_cmd(token));
	ft_memset(&p, 0, sizeof(t_path));
	i = 0;
	while (token)
	{
		data->cmd[i].id = i;
		data->cmd[i].cmd = get_cmd(token);
		data->cmd[i].path = find_path(data->env, data->cmd[i].cmd[0], p);
		set_fd(&(data->cmd[i]), data);
		while (token->type == WORD && token->next)
			token = token->next;
		token = token->next;
		i++;
	}
}