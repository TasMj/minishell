/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:57:45 by tas               #+#    #+#             */
/*   Updated: 2023/04/04 19:25:58 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int determine_type(char *token)
{
    if (check_heredoc(token) == 1) // rediriger une entrée stdin depuis de terminal. On peut ecrire puis entrer, etc
        return (1);
    else if (check_append(token) == 1) //contenu ajouté à la fin du doc existant
        return (2);
    else if (check_redir_in(token[0]) == 1) //redirige l'entrée standard en provenance d'un fichier
        return (3);
    else if (check_redir_out(token[0]) == 1) //remplace complètement son contenu
        return (4);
    else if (ft_strncmp(token, "|", 1) == 0)
        return (5);
    else if (ft_strncmp(token, "\0", 1) == 0)
        return (6);
    return (0);
}

/* determine type of each token*/
void    get_type(t_list **list_token)
{
    t_list *tmp;

    tmp = *list_token;
    while ((*list_token))
    {
        (*list_token)->type = determine_type((*list_token)->content);
        (*list_token) = (*list_token)->next;
    }
    (*list_token) = tmp;
}
