/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:57:45 by tas               #+#    #+#             */
/*   Updated: 2023/05/22 12:08:38 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	determine_type(char *token)
{
    if (check_heredoc(token) == 1)
        return (HEREDOC);
    else if (check_append(token) == 1) 
        return (APPEND);
    else if (check_redir_in(token[0]) == 1)
        return (STDIN);
    else if (check_redir_out(token[0]) == 1)
        return (STDOUT);
    else if (ft_strncmp(token, "|", 1) == 0)
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
