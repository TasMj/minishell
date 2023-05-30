/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 01:58:38 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/30 13:44:48 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_cmd(t_cmd *cmd)
{
	free_list(cmd->token);
	free_list(cmd->cmd);
	if (cmd->tab)
		free_tab(cmd->tab);
	if (cmd->tab_env)
		free_tab(cmd->tab_env);
	if (cmd->nb_redir > 0)
		free_tab(cmd->file);
	if (cmd->redir)
		free(cmd->redir);
	if (cmd->path)
		free(cmd->path);
}

void	destroy_all(t_xek *x)
{
	int	i;

	i = 0;
	while (i < x->nb_cmd)
	{
		free_cmd(&(x->cmd[i]));
		i++;
	}
	free(x->cmd);
	close(x->pipe[0]);
	close(x->pipe[1]);
	close(x->prev_pipe[0]);
	close(x->prev_pipe[1]);
}
