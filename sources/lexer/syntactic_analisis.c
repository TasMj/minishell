/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntactic_analisis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:19:12 by tas               #+#    #+#             */
/*   Updated: 2023/03/10 15:48:03 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* étapes */
/* Vérifier que la séquence d'elt lexicaux créée pdt l'analyse lexical est cohérente avec la grammaire du langage (respecte règles syntaxiques)*/

//1 création de l'arbre syntaxique: séquence d'éléments lexicaux est analysée pour créer un arbre s, qui représente la structure syntaxique de l'expression
//2 Validation de la grammaire: arbre validé pour assurer qu'il respect regle de grammaire. ex: vérifie que les opérateurs sont utilisés correctement, instruction correctement imbriqués
//3 detection erreurs de syntaxe
//4 gestion des priorités: inclure étape pour gerer prio des opérateurs
//5 transformation de l'arbre

/* determine the command type*/
void    get_type(t_list *list_token)
{
    if (is_word((*list_token).content) == 1) // add our own builtin
        (*list_token).type = WORD;
    else if (determine_type((*list_token).content) == 1)
        (*list_token).type = HEREDOC;
    else if (determine_type((*list_token).content) == 2)
        (*list_token).type = APPEND;
    else if (determine_type((*list_token).content) == 3)
        (*list_token).type = STDIN;
    else if (determine_type((*list_token).content) == 4)
        (*list_token).type = STDOUT;
    else if (determine_type((*list_token).content) == 5)
        (*list_token).type = PIPE;
    else if (determine_type((*list_token).content) == 6)
        (*list_token).type = END;
}



/* création de l'arbre syntaxique */
//placer dans un tableau
// int check_syntaxe(t_list **list_token)
// {
//     int    **operator[] = {WORD, PIPE, STDIN, APPEND, STDOUT, HEREDOC};

    
// }




// une fois ordonné, donner un index
/* check la cohérence de l'arbre */

/* gestion des prios (peut etre ajouter index de prio pour l'exec)*/