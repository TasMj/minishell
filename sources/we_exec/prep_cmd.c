/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:21:12 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/28 17:28:46 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	fill_cmd(t_cmd *cmd)
{
	cmd->cmd = clone_to_op(*(cmd->token));
	print_list(cmd->cmd);
	printf("\n");
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
