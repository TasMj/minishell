/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyze.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:36:17 by tas               #+#    #+#             */
/*   Updated: 2023/02/27 13:05:37 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* étapes */

//1 chaîne de caractères de la ligne de commande lue et stockée
//2 elimination des caractères blancs (espace, tab, retour à la ligne)
//3 détéction des guillemets
//4 division en tokens
//5 retour des tokens