/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:06:03 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/26 13:30:16 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_word(char *tok)
{
	if (check_redir_in(tok[0]) == 1 || check_redir_out(tok[0]) == 1 ||
		check_append(tok) == 1 || check_heredoc(tok) == 1)
		return (0);
	return (1);
}

int	size_to_op(char **cmd)
{
	int	i;

	i = 0;
	while (is_word(cmd[i]) == 1)
		i++;
	return (i);
}

// Converti les tokens d'une list en char **
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
