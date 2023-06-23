/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 03:54:06 by tas               #+#    #+#             */
/*   Updated: 2023/06/23 04:51:24 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

/******************************************************************************/
/*                                includes                                    */
/******************************************************************************/
#include "minishell.h"

/******************************************************************************/
/*                                fonctions                                   */
/******************************************************************************/

int     err_msg(int n);
void	free_tab(char **tab);
void    free_list_token_content(t_list **list_token);
void	free_list(t_list **list);
void	free_all(char *s1, char *s2);
void	free_end(t_minishell *data);



#endif