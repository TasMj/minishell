/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 03:31:12 by tas               #+#    #+#             */
/*   Updated: 2023/06/23 04:51:20 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/******************************************************************************/
/*                                includes                                    */
/******************************************************************************/
#include "minishell.h"

/******************************************************************************/
/*                                fonctions                                   */
/******************************************************************************/

int     exec_builtin(t_cmd *cmd, t_minishell *data);
char	*find_path(char **env, char *token);
void	ctrl_c(int sigid);
void	ctr_bs(int sigid);
void	dup_pipe(t_cmd *cmd, t_xek *x);
int     open_n_dup(t_cmd *cmd, t_xek *x);
int     is_builtin(t_cmd *cmd);
int     exec_it(t_cmd *cmd);
void	close_all(t_xek *x);
void    free_cmd(t_cmd *cmd);
void	destroy_exec(t_xek *x);
int     nb_hdoc(t_minishell *data);
int     exec_heredoc(t_minishell *data);
int     we_exec(t_minishell *data);
int     nb_redir(t_list	*elem);
int     handle_redir(t_cmd *cmd, t_list *elem);
int     open_pipes(t_minishell *data);
int     prep_cmd(t_minishell *data);




#endif