/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:52:27 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/05 17:26:00 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Compte le nombres de redir dans le token de cmd
-> {cat < file} => 1 redir */
int	nb_redir(t_list	*elem)
{
	int	count;

	count = 0;
	while (elem)
	{
		if (elem->type != WORD)
			count++;
		elem = elem->next;
	}
	return (count);
}

int	set_tools(t_cmd *cmd)
{
	cmd->redir = malloc(sizeof(int) * cmd->nb_redir);
	if (!cmd->redir)
		return (1);
	cmd->file = ft_calloc(sizeof(char *) * (cmd->nb_redir + 1), sizeof(char *));
	if (!cmd->file)
		return (1);
	return (0);
}

/* Enregistre les redirections avec leur type et leur file associes
-> cat < file */
int	handle_redir(t_cmd *cmd, t_list *elem)
{
	int	i;

	cmd->nb_redir = nb_redir(*(cmd->token));
	if (cmd->nb_redir == 0)
		return (0);
	if (set_tools(cmd) != 0)
		return (1);
	i = 0;
	while (elem)
	{
		if (elem->type != WORD)
		{
			cmd->redir[i] = elem->type;
			if (elem->next)
				cmd->file[i] = ft_strdup(elem->next->content);
			else
				return (1);
			if (!cmd->file[i])
				return (1);
			i++;
		}
		elem = elem->next;
	}
	cmd->file[i] = 0;
	return (0);
}
