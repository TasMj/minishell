/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 04:00:25 by tas               #+#    #+#             */
/*   Updated: 2023/07/06 02:33:29 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/******************************************************************************/
/*                                includes                                    */
/******************************************************************************/
# include "minishell.h"

/******************************************************************************/
/*                                fonctions                                   */
/******************************************************************************/

int		check_redir_in(char c);
int		check_redir_out(char c);
int		check_heredoc(char *str);
int		check_append(char *str);
int		is_redir(char *str);
char	*get_input(t_minishell *data);
t_list	**create_token(t_list **list_token, char *input);
int		syntax_error(t_minishell *data);
int		err_quote(t_list **list_token, t_minishell *data);
void	reunite_token(t_list **list_token);
int		check_pair_quote(char *str);
char	*remove_quotes(char *str);
void	remove_list_quotes(t_list **list_token);
void	substitute_dollar(t_minishell *data);
char	*sub_quotes(char *token, t_substitution *s, t_minishell *data);
int		check_dollar(char *str);
char	*substitution(t_minishell *data, char *token);
void	quote_sub(t_substitution *s, int a, t_minishell *data);
char	*remove_quote_end(t_substitution *s, t_minishell *data);
void	get_type(t_list **list_token);
int		err_redir(t_minishell *data);

#endif