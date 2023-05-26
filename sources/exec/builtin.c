/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:42:19 by tmejri            #+#    #+#             */
/*   Updated: 2023/05/26 19:43:46 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

int	exec_builtin(t_list **list_token)
{
	(void) list_token;
	t_list	*tmp;

	if (!list_token || ft_lstsize(*list_token) == 0)
		return (-1);
	tmp = *list_token;
	if (ft_strlen((*list_token)->content) == 2 && ft_strncmp((*list_token)->content, "cd", 2) == 0)
		ft_cd(list_token);
	else if (ft_strlen((*list_token)->content) == 4 && ft_strncmp((*list_token)->content, "echo", 4) == 0)
		ft_echo(list_token);
	else if (ft_strlen((*list_token)->content) == 3 &&ft_strncmp((*list_token)->content, "env", 3) == 0)
		ft_env(list_token);
	else if (ft_strlen((*list_token)->content) == 4 && ft_strncmp((*list_token)->content, "exit", 4) == 0)
		exit(1);
	else if (ft_strlen((*list_token)->content) == 6 &&ft_strncmp((*list_token)->content, "export", 6) == 0)
		ft_export(list_token);
	else if (ft_strlen((*list_token)->content) == 3 && ft_strncmp((*list_token)->content, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strlen((*list_token)->content) == 5 && ft_strncmp((*list_token)->content, "unset", 5) == 0)
		ft_unset(list_token);
	else
		return (1);
	*list_token = tmp;
	// printf("bultin\n");
	return (0);
}
