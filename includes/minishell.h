/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:49:25 by tmejri            #+#    #+#             */
/*   Updated: 2023/06/23 12:15:33 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

/******************************************************************************/
/*                                includes                                    */
/******************************************************************************/

/* library */
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

/* headers */
#include "struct.h"
#include "builtin.h"
#include "exec.h"
#include "exit.h"
#include "parsing.h"
#include "tools.h"

/******************************************************************************/
/*                                  macros                                    */
/******************************************************************************/

/*Errors*/
# define ERR_REDIR_IN_OUT "syntax error near unexpected token `newline'\n"
# define ERR_QUOTE "not handle by minishell\n"
# define ERR_CMD "command not found\n"
# define ERR_MANY_ARG "too many arguments (WIP)\n"
# define ERR_HOME "HOME not set\n"
# define ERR_EXPORT "not a valid identifier\n"

/******************************************************************************/
/*                            global variable                                 */
/******************************************************************************/
extern t_list	**g_list_env;

/******************************************************************************/
/*                                   enum                                     */
/******************************************************************************/

enum token_type {
	WORD,
	APPEND,
	HEREDOC,
	STDIN,
	STDOUT,
	PIPE,
	END
};

// /******************************************************************************/
// /*                               structures                                   */
// /******************************************************************************/

// typedef struct s_list
// {
// 	char			*content;
// 	int				type;
// 	int				index;
// 	int				flag_space;
// 	int				flag_quote;
// 	struct s_list	*next;
// }	t_list;

// typedef struct s_substitution
// {
//     char    *var_substitute;
//     char    *keep_var;
//     char	*keep_var2;
//     char    *new_content;
//     char    *without_dollar;
//     char	*stock;
//     int		start;
//     int		end;
//     int		deb;
//     int		i;
// 	int		flag;
// 	int		flag_space;
// 	int		flag_keep_quote;
// 	int		quote;
// }	t_substitution;

// typedef struct s_data
// {
// 	pid_t	pid;
// 	char	*cmd;
// 	char	*path_cmd;
// 	char	**token_cmd;
// }	t_data;

// typedef struct s_path
// {
// 	int		i;
// 	int		j;
// 	char	*path_with_points;
// 	char	*path_without;
// 	char	**path_split;
// }	t_path;

// typedef struct s_exec
// {
// 	t_list	**token;
// 	// t_cmd	*cmd;
// 	char	**env;
// 	int		**fd;
// 	int		nb_pipes;
// 	int		nb_cmd;
// }	t_exec;

// typedef struct s_cmd
// {
// 	int		id;
// 	t_list	**token;
// 	t_list	**cmd;
// 	char	**tab;
// 	char	*path;
// 	int		*redir;
// 	char	**file;
// 	int		nb_redir;
// 	pid_t	pid;
// 	char	**tab_env;
// 	struct s_minishell *data;
// }	t_cmd;

// typedef struct	s_hdoc
// {
// 	char	*delim;
// 	int		hd_pipe[2];
// }	t_hdoc;

// typedef struct s_xek
// {
// 	t_cmd		*cmd;
// 	int			nb_cmd;
// 	int			**pipe;
// 	int			nb_hdoc;
// 	t_hdoc		*hdoc;
// 	int			hdoc_index;
// }	t_xek;

// typedef struct s_minishell
// {
// 	char			*input;
// 	t_list			**token;
// 	int				code_err;
// 	struct s_xek	*x;
// }	t_minishell;

// typedef struct s_heredoc
// {
//     char    *delimiteur;
// 	pid_t	pid;
//     int     tube[2];
// 	char	*cmd;
// 	char	*path_cmd;
// 	char	**token_arg;
// } t_heredoc;

// typedef struct s_redir
// {
// 	int		fd;
// 	pid_t	pid;
//     int     tube[2];
// 	char	*cmd;
// 	char	*file_name;
// 	char	*path_cmd;
// 	char	**token_arg;

// }t_redir;

// typedef struct s_echo
// {
//     t_list  *tmp;
//     char    *stockage;
//     int     flag;
//     int     to_free;
// }t_echo;

// typedef struct s_min_max
// {
// 	int		min;
// 	int		max;
// }t_min_max;



#endif