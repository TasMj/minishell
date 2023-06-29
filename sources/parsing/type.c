/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:57:45 by tas               #+#    #+#             */
/*   Updated: 2023/06/27 14:00:07 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	determine_type(char *token)
{
	if (ft_strlen(token) == 2 && check_heredoc(token) == 1)
		return (HEREDOC);
	else if (ft_strlen(token) == 2 && check_append(token) == 1)
		return (APPEND);
	else if (ft_strlen(token) == 1 && check_redir_in(token[0]) == 1)
		return (STDIN);
	else if (ft_strlen(token) == 1 && check_redir_out(token[0]) == 1)
		return (STDOUT);
	else if (ft_strlen(token) == 1 && ft_strncmp(token, "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(token, "\0", 1) == 0)
		return (END);
	return (0);
}

/* determine type of each token*/
void	get_type(t_list **list_token)
{
	t_list	*tmp;

	tmp = *list_token;
	while ((*list_token))
	{
		(*list_token)->type = determine_type((*list_token)->content);
		(*list_token) = (*list_token)->next;
	}
	(*list_token) = tmp;
}
