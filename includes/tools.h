/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 04:17:24 by tas               #+#    #+#             */
/*   Updated: 2023/06/27 12:10:50 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

/******************************************************************************/
/*                                includes                                    */
/******************************************************************************/
#include "minishell.h"

/******************************************************************************/
/*                                fonctions                                   */
/******************************************************************************/

char	    **ft_split(char const *s, char c);
int         count_slash(char *str);
int         check_list_equal(t_list **list);
char	    *del_equal(char *str);
char	    *after_equal(char *str);
int         is_in_env(char *str);
t_list	    **ft_copy_list(t_list **copy);
void	    print_export(t_list **list);
t_list	    **sort_env(t_list **list);
int         ft_isalpha(char *str);
int         extract_str(char *str);
t_list	    *ft_lstlast(t_list *lst);
void	    add_list(t_list **list_token, char *stockage, int flag_space);
int         ft_lstsize(t_list *lst);
int         is_a_space(char c);
int         is_a_separator(char c);
void	    remove_empty_tokens(t_list **list);
char	    *get_venv(char *str);
void	    *ft_memset(void *s, int c, size_t n);
char	    *ft_strdup(char *s);
char	    *ft_strdup_size(char *s, int size);
int         ft_strlen(char *str);
char	    *ft_strjoin_mod(char *s1, char *s2, int mode);
int         ft_strncmp(char *s1, char *s2, size_t n);
char	    *ft_strjoin(char *s1, char *s2);
long long	ft_atoi(const char *nptr);
void	    *ft_calloc(size_t n, size_t size);
int         ft_strcmp(char *s1, char *s2);
char	    *ft_itoa(int n);
char	    **lst_to_tab(t_list **lst);
int	        nb_cmd(t_list *token);
void	    set_to_zero(t_xek *x);
int		has_slash(t_cmd *cmd);
t_list	*ft_lstnew(char *input, int flag_space);
void	ft_lstadd_back(t_list **lst, t_list *new);

#endif