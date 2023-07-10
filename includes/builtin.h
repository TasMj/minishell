/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 03:02:40 by tas               #+#    #+#             */
/*   Updated: 2023/07/10 22:24:42 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

/******************************************************************************/
/*                                includes                                    */
/******************************************************************************/
# include "minishell.h"

/******************************************************************************/
/*                                fonctions                                   */
/******************************************************************************/

int		ft_cd(t_cmd *cmd, t_minishell *data);
int		ft_echo(t_list **list_token);
t_list	**get_list_env(char **env);
int		ft_env(t_list **l, t_minishell *data);
void	ft_exit(t_minishell *data);
void	ft_exit_code(t_cmd *cmd, t_minishell *data);
int		ft_export(t_list **list_token, t_minishell *data);
void	ft_pwd(void);
int		ft_unset(t_list **list_token, t_minishell *data);
int		modify_pwd(char *new_pwd, t_minishell *data);

#endif
