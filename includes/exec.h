/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 03:31:12 by tas               #+#    #+#             */
/*   Updated: 2023/07/05 13:18:16 by jthuysba         ###   ########.fr       */
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
void	ctrl_c(int sigid);
void	ctr_bs(int sigid);
void	dup_pipe(t_cmd *cmd, t_xek *x);
int     open_n_dup(t_cmd *cmd, t_xek *x);
int     is_builtin(t_cmd *cmd);
int	    exec_it(t_cmd *cmd, t_minishell *data);
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
int     handle_builtin(t_cmd *cmd, t_minishell *data);
void	handle_signal(int sigid);
void	signal_ignore(void);
void	set_signal(void);
void	ctr_bs(int sigid);
void	signal_heredoc(int sig, t_minishell *data);
void sub_dollar_hdoc(t_substitution *s, char *str, t_minishell *data);
t_minishell *singleton_minishell(void);
void	signal_signal();
void	signal_default(void);
void	handle_signal_hdoc(void);
int	handle_pwd(t_cmd *cmd);
int	exec_it(t_cmd *cmd, t_minishell *data);

#endif