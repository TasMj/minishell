/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:30:38 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/28 16:31:56 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Retourne le nombre de commandes */
int	nb_cmd(t_list *token)
{
	int	count;

	count = 0;
	if (token->type == WORD)
		count++;
	while (token)
	{
		if (token->type == PIPE)
			count++;
		token = token->next;
	}
	return (count);
}

/* Memset toutes les commandes */
void	set_to_zero(t_xek *x)
{
	int	i;

	i = 0;
	while (i < x->nb_cmd)
	{
		ft_memset(&(x->cmd[i]), 0, sizeof(t_cmd));
		i++;
	}
}
