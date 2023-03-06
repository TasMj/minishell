/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntactic_analisis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:19:12 by tas               #+#    #+#             */
/*   Updated: 2023/03/03 13:01:23 by tas              ###   ########.fr       */
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

