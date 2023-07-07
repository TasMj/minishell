/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 03:54:06 by tas               #+#    #+#             */
/*   Updated: 2023/07/06 02:30:26 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

/******************************************************************************/
/*                                includes                                    */
/******************************************************************************/
# include "minishell.h"

/******************************************************************************/
/*                                fonctions                                   */
/******************************************************************************/

int		err_msg(int n, char *msg_err, int code_err);
void	free_tab(char **tab);
void	free_list_token_content(t_list **list_token);
void	free_list(t_list **list);
void	free_all(char *s1, char *s2);
void	free_end(t_minishell *data);
int		handle_exit(t_cmd *cmd, t_minishell *data);
int		free_and_ret(char *s1, char *s2, int ret);
void	free_main_tools(t_minishell *data);

#endif
