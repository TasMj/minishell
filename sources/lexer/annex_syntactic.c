/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   annex_syntactic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:57:45 by tas               #+#    #+#             */
/*   Updated: 2023/03/08 13:59:31 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_word(char *token)
{
    char    *env_path;
    char    **path;
    char    *full_path;
    struct  stat buffer;
    int     is_executable;
    int     i;
    
    if ((!token) || token[0] == '\0')
        return (2);
    env_path = getenv("PATH");
    path = ft_split(env_path, ':');
    i = 0;    
    while (path[i])
    {
        full_path = ft_strjoin_mod(path[i], "/", 0);
        full_path = ft_strjoin_mod(full_path, token, 1);
        is_executable = !access(full_path, X_OK);
        if (stat(full_path, &buffer) == 0 && is_executable)
            return (1);
        i++;
    }
    return (0);
}

int determine_type(char *token)
{
    if (check_heredoc(token) == 2) // rediriger une entrée stdin depuis de terminal. On peut ecrire puis entrer, etc
        return (1);
    else if (check_heredoc(token) == 3) //contenu ajouté à la fin du doc existant
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
