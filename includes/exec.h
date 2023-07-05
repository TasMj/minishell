/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 03:31:12 by tas               #+#    #+#             */
/*   Updated: 2023/07/05 18:12:15 by jthuysba         ###   ########.fr       */
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

char	*find_path(char **env, char *token);
void	dup_pipe(t_cmd *cmd, t_xek *x);
int     open_n_dup(t_cmd *cmd, t_xek *x);
int     is_builtin(t_cmd *cmd);
int	    exec_it(t_cmd *cmd, t_minishell *data);
void	close_all(t_xek *x);
void    free_cmd(t_cmd *cmd);
void	destroy_exec(t_xek *x);
int     we_exec(t_minishell *data);
int     nb_redir(t_list	*elem);
int     handle_redir(t_cmd *cmd, t_list *elem);
int     open_pipes(t_minishell *data);
int     prep_cmd(t_minishell *data);
int     handle_builtin(t_cmd *cmd, t_minishell *data);
int		handle_pwd(t_cmd *cmd);
int		exec_it(t_cmd *cmd, t_minishell *data);
int		open_n_leave(t_list	*token);
int		cmd_access(t_cmd *cmd, char *msg_err);
int		set_prep_tools(t_minishell *data);
void	add_lst_type(t_list **list_token, t_list *elem);


#endif