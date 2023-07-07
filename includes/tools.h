/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 04:17:24 by tas               #+#    #+#             */
/*   Updated: 2023/07/06 02:55:44 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

/******************************************************************************/
/*                                includes                                    */
/******************************************************************************/
# include "minishell.h"

/******************************************************************************/
/*                                fonctions                                   */
/******************************************************************************/

char		**ft_split(char const *s, char c);
int			count_slash(char *str);
int			check_list_equal(t_list **list);
char		*del_equal(char *str);
char		*after_equal(char *str);
int			is_in_env(char *str);
t_list		**ft_copy_list(t_list **copy);
void		print_export(t_list **list);
t_list		**sort_env(t_list **list);
int			ft_isalpha(char *str);
int			is_numeric(char *str);
int			extract_str(char *str);
t_list		*ft_lstlast(t_list *lst);
void		add_list(t_list **list_token, char *stockage, int flag_space);
int			ft_lstsize(t_list *lst);
int			is_a_space(char c);
int			is_a_separator(char c);
void		remove_empty_tokens(t_list **list);
char		*get_venv(char *str);
void		*ft_memset(void *s, int c, size_t n);
char		*ft_strdup(char *s);
char		*ft_strdup_size(char *s, int size);
int			ft_strlen(char *str);
char		*ft_strjoin_mod(char *s1, char *s2, int mode);
int			ft_strncmp(char *s1, char *s2, size_t n);
char		*ft_strjoin(char *s1, char *s2);
long long	ft_atoi(const char *nptr);
void		*ft_calloc(size_t n, size_t size);
int			ft_strcmp(char *s1, char *s2);
char		*ft_itoa(int n);
char		**lst_to_tab(t_list **lst);
int			nb_cmd(t_list *token);
void		set_to_zero(t_xek *x);
int			has_slash(t_cmd *cmd);
t_list		*ft_lstnew(char *input, int flag_space);
void		ft_lstadd_back(t_list **lst, t_list *new);
int			is_dir(char *path);
int			err_write(char *error, int code_err);
int			check_equal(char *str);
int			ft_isalnum(int c);
void		add_space(t_minishell *data);
int			contain_slash(char *str);
int			is_abc(char c);
int			is_alphanum(char *str);
int			contain_exclam(char *str);
int			put_str_err(char *error);
size_t		nbr_len(long int n);
t_list		*ft_lst_prev(t_list *elem, t_list *first);
int			invalid_option(t_cmd *cmd, t_cd *c);
int			end_cd(t_cmd *cmd, t_cd *c);
int			intit_cd(t_cmd *cmd, t_cd *c);
int			home_unset(t_cd *c);
int			cd_one_tok(t_cmd *cmd, t_cd *c);
void		dir_err(t_cmd *cmd, char *path);
void		chdir_err(t_cmd *cmd, char *path);
int			err_nb_cmd(t_cmd *cmd, char *path);
int			handl_root(t_cmd *cmd, t_cd *c);
int			cd_directory(t_cd *c, t_cmd *cmd);
int			cd_home(t_cmd *cmd, t_cd *c);
int			is_dir(char *path);
int			go_chdir(t_cmd *cmd, t_cd *c);
int			set_old_path(char *path);
int			end_cd(t_cmd *cmd, t_cd *c);
int			err_cd(t_cmd *cmd, char *path);
char		*set_path(char *path, t_list **list);
int			invalid_option(t_cmd *cmd, t_cd *c);
int			end_cd(t_cmd *cmd, t_cd *c);
int			intit_cd(t_cmd *cmd, t_cd *c);
int			home_unset(t_cd *c);
int			cd_one_tok(t_cmd *cmd, t_cd *c);
int			handl_root(t_cmd *cmd, t_cd *c);
int			cd_directory(t_cd *c, t_cmd *cmd);
int			go_chdir(t_cmd *cmd, t_cd *c);
int			cd_home(t_cmd *cmd, t_cd *c);
int			is_dir(char *path);
void		dir_err(t_cmd *cmd, char *path);
void		chdir_err(t_cmd *cmd, char *path);
int			err_cd(t_cmd *cmd, char *path);
char		*set_path(char *path, t_list **list);
int			err_nb_cmd(t_cmd *cmd, char *path);
int			set_old_path(char *path);
char		*get_previous_dir(char *str);
int			modify_pwd(char *new_pwd);
int			ft_cd(t_cmd *cmd);
int			err_add_env(char *msg_err, char *stock, char *copy);
void		err_exclam(char *msg_err, char *stock, char *copy);
int			add_modif(char *copy, char *stock, t_list *tmp);
char		*set_stock(char *str, char *stock);
int			add_var_env(char *stock, t_list *tmp);
int			modify_var(char *stock, t_list *tmp);
int			ft_strlen(char *str);
int			ft_strlen_var(char *str);
void		put_nbr(char *str, long int n, size_t i);
char		*var_name(char *str);
int			check_var(char *str);
char		*set_tmp(char *tmp, t_substitution *s);
void		in_substitution(t_substitution *s, t_minishell *data);
void		sub_rest(t_substitution *s, char *str);
void		hdoc_exclam(t_substitution *s, char *str, t_minishell *data);
void		go_to_dollar(t_substitution *s, t_minishell *d);
void		quotes_next_to_dollar(t_minishell *data, t_substitution *s);
int			space_only(char *p);

#endif