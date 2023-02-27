/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantical_analyze.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:06:38 by tas               #+#    #+#             */
/*   Updated: 2023/02/27 13:17:32 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* étapes */
/*but : vérifier que les elt lexicaux et les expressions syntaxiques crées pdt les étapes précédentes
sont cohérentes sémantiquement parlant: qu'ils ont un sens et une interprétation valides*/

//1 verificaton des types. ex: les opérateurs sont appliqués à des types compatibles, les fonctions sont appelées avec les bons arguments, les var sont déclarées et initialisées correctement
//2 Résolution des noms: les noms des fonctions, variables, et autres symboles sont résolus: ex verif que fonctions appelées avc le bon nom
    //que les var sont déclarées avant leur utilisation, symboles def dans le bon espace de nom, etc
//3 Analyse de flux de contrôle: on verifie que instructions de boucle ont des contions d'arrêt valide, instructions d'exception correctement gérée, etc
//4 génération de code intermediaire: une fois que elt lexicaux et expression ont été verif sémantiquement, un code interm peut être généré pour faciliter l'opti et la generation du code final