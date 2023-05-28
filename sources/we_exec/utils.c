/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:30:38 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/28 19:59:16 by jthuysba         ###   ########.fr       */
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
