/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:30:38 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/30 19:53:00 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Converti les token d'une liste en char ** */
char	**lst_to_tab(t_list **lst)
{
	t_list	*elem;
	char	**tab;
	int	i;

	elem = *lst;
	tab = malloc(sizeof(char *) * (ft_lstsize(*lst) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (elem)
	{
		tab[i] = ft_strdup_size(elem->content, ft_strlen(elem->content));
		elem = elem->next;
		i++;
	}
	tab[i] = 0;
	return (tab);
}

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
		x->cmd[i].tab_env = 0;
		i++;
	}
}

/* Check si la commande a un slash et est donc un path
ex : /bin/ls, /jules */
int	has_slash(t_cmd *cmd)
{
	int	i;
	i = 0;
	while ((*cmd->cmd)->content[i])
	{
		if ((*cmd->cmd)->content[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
