/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:21:12 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/28 19:59:00 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

/* On clone les token jusqua un pipe ou la fin
-> {cat < file} */
t_list	**clone_to_pipe(t_list *token)
{
	t_list	**lst;
	t_list	*elem;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	*lst = NULL;
	elem = token;
	while (elem && elem->type != PIPE)
	{
		add_list(lst, elem->content, elem->flag_space);
		elem = elem->next;
	}
	get_type(lst);
	return (lst);
}

/* Retourne la commande brut sans les redir
-> {cat} {wc -l}, etc) */
t_list	**clone_to_op(t_list *token)
{
	t_list	**lst;
	t_list	*elem;

	elem = token;
	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	*lst = NULL;
	while (elem && elem->type == WORD)
	{
		add_list(lst, elem->content, elem->flag_space);
		elem = elem->next;
	}
	return (lst);
}

/* Enregistre les redirections avec leur type et leur file associes
-> cat < file */
int	handle_redir(t_cmd *cmd, t_list *elem)
{
	int	i;

	cmd->nb_redir = nb_redir(*(cmd->token));
	cmd->redir = malloc(sizeof(int) * cmd->nb_redir);
	if (!cmd->redir)
		return (1);
	cmd->file = malloc(sizeof(char *) * cmd->nb_redir + 1);
	if (!cmd->file)
		return (1);
	i = 0;
	while (elem)
	{
		if (elem->type != WORD)
		{
			cmd->redir[i] = elem->type;
			cmd->file[i] = ft_strdup(elem->next->content);
			if (!cmd->file[i])
				return (1);
			i++;
		}
		elem = elem->next;
	}
	return (0);
}

int	fill_cmd(t_cmd *cmd)
{
	char	**tab;

	/* On attribue a cmd la commande sans les op */
	cmd->cmd = clone_to_op(*(cmd->token));

	tab = lst_to_tab(g_list_env);
	cmd->path = find_path(tab, (*cmd->cmd)->content);
	free(tab);

	handle_redir(cmd, *(cmd->token));
	
	return (0);
}

/* Setup les commandes en t_cmd */
int	prep_cmd(t_minishell *data)
{
	t_list	*elem;
	int	i;

	/* On compte les commandes en fonction des pipes
	-> 1 pipe => 2 commandes */
	data->x->nb_cmd = nb_cmd(*data->token);
	data->x->cmd = malloc(sizeof(t_cmd) * data->x->nb_cmd);
	if (!data->x)
		return (1);
	set_to_zero(data->x);
	
	elem = *(data->token);
	i = 0;
	while (elem)
	{
		/* On initialise tous les param de chaque cmd */
		data->x->cmd[i].id = i;
		data->x->cmd[i].token = clone_to_pipe(elem);
		fill_cmd(&(data->x->cmd[i]));

		while (elem && elem->type != PIPE)
			elem = elem->next;
		if (elem && elem->type == PIPE)
			elem = elem->next;
		i++;
	}
	return (0);
}
