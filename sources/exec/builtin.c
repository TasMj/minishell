/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:42:19 by tmejri            #+#    #+#             */
/*   Updated: 2023/05/27 12:06:22 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

int	exec_builtin(t_list **lst)
{
	t_list	*tmp;

	if (!lst || ft_lstsize(*lst) == 0)
		return (-1);
	tmp = *lst;
	if (ft_strlen((*lst)->content) == 2 && ft_strncmp((*lst)->content, "cd", 2) == 0)
		ft_cd(lst);
	else if (ft_strlen((*lst)->content) == 4 && ft_strncmp((*lst)->content, "echo", 4) == 0)
		ft_echo(lst);
	else if (ft_strlen((*lst)->content) == 3 && ft_strncmp((*lst)->content, "env", 3) == 0)
		ft_env(lst);
	else if (ft_strlen((*lst)->content) == 4 && ft_strncmp((*lst)->content, "exit", 4) == 0)
		exit(1);
	else if (ft_strlen((*lst)->content) == 6 && ft_strncmp((*lst)->content, "export", 6) == 0)
		ft_export(lst);
	else if (ft_strlen((*lst)->content) == 3 && ft_strncmp((*lst)->content, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strlen((*lst)->content) == 5 && ft_strncmp((*lst)->content, "unset", 5) == 0)
		ft_unset(lst);
	else
		return (1);
	*lst = tmp;
	return (0);
}
