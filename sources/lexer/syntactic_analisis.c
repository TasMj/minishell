/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntactic_analisis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:19:12 by tas               #+#    #+#             */
/*   Updated: 2023/03/08 16:26:00 by tas              ###   ########.fr       */
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
int check_syntaxe(t_list **list_token)
{
    int    *operator[] = {PIPE, STDIN, APPEND, STDOUT, HEREDOC};
    int     i;
    int     c;
    char    *tab_before;        
    char    *tab_after;
    t_list  *beginning;

    beginning = *list_token;
    while((*list_token) != NULL)
    {
        i = 0;
        c = 0;
        while (operator[i])
        {
            if ((*list_token)->type == operator[i])
            {
                tab_before = malloc(sizeof(char*) * c + 1);
                
            }
            else
            {
                i++;
                c++;
            }
        }
        (*list_token) = (*list_token)->next;
    }
    
        
}




// une fois ordonné, donner un index
/* check la cohérence de l'arbre */

/* gestion des prios (peut etre ajouter index de prio pour l'exec)*/