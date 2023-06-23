/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:02:44 by jthuysba          #+#    #+#             */
/*   Updated: 2023/06/23 12:19:11 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Retourne le nombre de pipes de la ligne de commande */
// static int	count_pipes(t_list *token)
// {
// 	int	count;

// 	count = 0;
// 	while (token)
// 	{
// 		if (token->type == PIPE)
// 			count++;
// 		token = token->next;
// 	}
// 	return (count);
// }

/* Ouvre toutes les pipes de la ligne de comande */
int	open_pipes(t_minishell *data)
{
	int	i;

	data->x->nb_cmd = nb_cmd(*(data->token));
	i = 0;
	if (data->x->nb_cmd <= 1)
		return (0);
	data->x->pipe = malloc(sizeof(int *) * data->x->nb_cmd - 1);
	while (i < data->x->nb_cmd - 1)
	{
		data->x->pipe[i] = malloc(sizeof(int) * 2);
		if (pipe(data->x->pipe[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}
