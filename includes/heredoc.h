/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:10:50 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/05 18:13:40 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

/******************************************************************************/
/*                                includes                                    */
/******************************************************************************/
#include "minishell.h"

/******************************************************************************/
/*                                fonctions                                   */
/******************************************************************************/

int		nb_hdoc(t_minishell *data);
void	free_hdoc_tools(t_hdoc *hdoc, char *input);
void	write_in_fd(char *str, int fd);
char	*substitute_hdoc(char *input, t_minishell *data);
void 	sub_dollar_hdoc(t_substitution *s, char *str, t_minishell *data);
int     nb_hdoc(t_minishell *data);
int     exec_heredoc(t_minishell *data);

#endif