/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:58:38 by jthuysba          #+#    #+#             */
/*   Updated: 2023/06/23 03:44:37 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	close_writing(t_xek *x)
// {
// 	int	i;

// 	i = 0;
// 	while (i < x->nb_cmd - 1)
// 	{
// 		close(x->pipe[i][1]);
// 		i++;
// 	}
// }

/* Close toutes les pipes */
void	close_all(t_xek *x)
{
	int	i;

	i = 0;
	while (i < x->nb_cmd - 1)
	{
		close(x->pipe[i][0]);
		close(x->pipe[i][1]);
		i++;
	}
	i = 0;
	while (i < x->nb_hdoc)
	{
		close(x->hdoc[i].hd_pipe[0]);
		i++;
	}
}

void free_cmd(t_cmd *cmd)
{
	if (cmd->token)
		free_list(cmd->token);
	if (cmd->cmd)
		free_list(cmd->cmd);
	if (cmd->tab)
		free_tab(cmd->tab);
	if (cmd->tab_env)
		free_tab(cmd->tab_env);
	if (cmd->file)
		free_tab(cmd->file);
	if (cmd->redir)
		free(cmd->redir);
	if (cmd->path)
		free(cmd->path);
}

static int	free_pipes(t_xek *x)
{
	int	i;

	i = 0;
	while (i < x->nb_cmd - 1)
	{
		free(x->pipe[i]);
		i++;
	}
	free(x->pipe);
	return (0);
}

void	destroy_exec(t_xek *x)
{
	int	i;

	i = 0;
	while (i < x->nb_cmd)
	{
		free_cmd(&(x->cmd[i]));
		i++;
	}
	free_pipes(x);
	close_all(x);
	free(x->hdoc);
	free(x->cmd);
	free(x);
}
