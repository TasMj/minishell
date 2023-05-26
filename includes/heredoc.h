/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:41:00 by tas               #+#    #+#             */
/*   Updated: 2023/05/26 11:47:50 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

/******************************************************************************/
/*                                includes                                    */
/******************************************************************************/
#include "minishell.h"
#include <fcntl.h>

/******************************************************************************/
/*                               structures                                   */
/******************************************************************************/
typedef struct s_heredoc
{
    char    *delimiteur;
	pid_t	pid;
    int     tube[2];
	char	*cmd;
	char	*path_cmd;
	char	**token_arg;
}t_heredoc;

typedef struct s_redir
{
	int		fd;
	pid_t	pid;
    int     tube[2];
	char	*cmd;
	char	*file_name;
	char	*path_cmd;
	char	**token_arg;

}t_redir;

typedef struct s_echo
{
    t_list  *tmp;
    char    *stockage;
    int     flag;
    int     to_free;
}t_echo;

typedef struct s_min_max
{
	int		min;
	int		max;
}t_min_max;

/******************************************************************************/
/*                            variable globale                                */
/******************************************************************************/

extern t_list	**g_list_env;

/******************************************************************************/
/*                                fonctions                                   */
/******************************************************************************/

/* tools */
char    *get_file_name(t_list **list_token, char *c);
char    *cmd_before_redir(t_list **list_token, t_redir *s);
void    init_redir(t_redir *s, t_list **list_token, char **env, char *c);
void	free_redir(t_redir *redir);

/* heredoc */
char    *cmd_before_heredoc(t_list **list_token, t_heredoc *h);
int     heredoc(t_list **list_token, char **env);
int     ft_strcmp(char *s1, char *s2);
int     heredoc_process(t_heredoc *h, char **env);
void	free_heredoc(t_heredoc *h);

/* Redirection */
int		stdin_process(t_list **list_token, char **env);
int		stdout_process(t_list **list_token, char **env);
int		append_process(t_list **list_token, char **env);


t_list  **get_list_env(char **env);

int    exec_builtin(t_list **list_token);

/*signals*/
void    ctrl_c(int sigid);
void    ctrl_d(int sigid);
void    ctr_bs(int sigid);

int		syntax_error(t_list **list_token);

int		count_slash(char *str);
int		check_equal(char *str);
char	*take_off_equal(char *str);
int		is_in_env(char *str);
t_list	**ft_copy_list(t_list **copy);
int		ft_strlen_var(char *str);
void	print_export(t_list **list);
int		is_sorted(t_list **list);
t_list	**sort_env(t_list **list);
int		sort_env_ascii(void);
int		ft_export(t_list **list_token);
void	set_min_max(t_list **list ,t_min_max *m);
int		is_sorted(t_list **list);
t_list	**sort_env(t_list **list);

void	free_heredoc(t_heredoc *h);

int	check_dollar(char *str);
char	*remove_space(char *str);
char	*substitution(char *token);
void	quote_sub(t_substitution *s, t_list *list_token, int a);
int		err_end(t_list **list_token);


#endif