/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:21:12 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/28 17:02:22 by jthuysba         ###   ########.fr       */
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
	print_list(lst);
	printf("\n");
	return (lst);
}

/* On va separer les token de chaque commande en fonction des pipes
-> {cat < file},{wc -l > file2} */
int	split_pipes(t_minishell *data)
{
	t_list	*elem;
	int		i;
	
	elem = (*data->token);
	i = 0;
	while (elem && i < data->x->nb_cmd)
	{
		data->x->cmd[i].token = clone_to_pipe(elem);
		if (!data->x->cmd[i].token)
			return (1);
		// print_list(data->x->cmd[i].token);
		while (elem && elem->type != PIPE)
			elem = elem->next;
		if (elem && elem->type == PIPE)
			elem = elem->next;
		i++;
	}
	return (0);
}

/* Setup les commandes en t_cmd */
int	prep_cmd(t_minishell *data)
{
	
	/* On compte les commandes en fonction des pipes
	-> 1 pipe => 2 commandes */
	data->x->nb_cmd = nb_cmd(*data->token);
	printf("cmd=%d\n", data->x->nb_cmd);
	data->x->cmd = malloc(sizeof(t_cmd) * data->x->nb_cmd);
	if (!data->x)
		return (1);
	// set_to_zero(data->x->cmd);
	
	if (split_pipes(data) != 0)
			return (1);
	return (0);
}
