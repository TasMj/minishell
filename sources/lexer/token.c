/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:03:06 by tas               #+#    #+#             */
/*   Updated: 2023/03/01 19:58:24 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* étapes */

//1 récuperer ligne de commande (fichier input)
//2 analyse lexicale : découper la ligne de commande en token grace aux séparateurs
    //espaces, tabulations
    //retour à la ligne
    //guillements
//3 Analyse syntaxique : identifier la structure syntaxique de la ligne de commande (le type)
//4 Analyse sémantique : interpréter les tokens pour leur donner un sens (ex identifier les cmd, les variables, les options,...)
//5 execution


// token detector
// parcourir tant qu'il n'y a pas d'espace 
// analyser le bout de mot