/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:14:14 by tas               #+#    #+#             */
/*   Updated: 2023/07/06 02:38:43 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/******************************************************************************/
/*                                includes                                    */
/******************************************************************************/
# include "minishell.h"

/******************************************************************************/
/*                               structures                                   */
/******************************************************************************/

typedef struct s_list
{
	char			*content;
	int				type;
	int				index;
	int				flag_space;
	int				flag_quote;
	int				quote_trace;
	struct s_list	*next;
}	t_list;

typedef struct s_substitution
{
	char			*var_substitute;
	char			*keep_var;
	char			*keep_var2;
	char			*new_content;
	char			*without_dollar;
	char			*stock;
	int				start;
	int				end;
	int				deb;
	int				i;
	int				flag;
	int				flag_space;
	int				flag_keep_quote;
	int				quote;
	t_list			*tmp;
	t_list			*prev;
	t_list			*starting;
	t_list			*reset;
}	t_substitution;

typedef struct s_data
{
	pid_t	pid;
	char	*cmd;
	char	*path_cmd;
	char	**token_cmd;
}	t_data;

typedef struct s_path
{
	int		i;
	int		j;
	char	*path_with_points;
	char	*path_without;
	char	**path_split;
}	t_path;

typedef struct s_cmd
{
	int					id;
	t_list				**token;
	t_list				**cmd;
	char				**tab;
	char				*path;
	int					*redir;
	char				**file;
	int					nb_redir;
	pid_t				pid;
	char				**tab_env;
	int					status;
	struct s_minishell	*data;
}	t_cmd;

typedef struct s_hdoc
{
	char	*delim;
	int		hd_pipe[2];
	int		flag_sub;
}	t_hdoc;

typedef struct s_xek
{
	t_cmd		*cmd;
	int			nb_cmd;
	int			**pipe;
	int			nb_hdoc;
	t_hdoc		*hdoc;
	int			hdoc_index;
}	t_xek;

typedef struct s_minishell
{
	char			*input;
	t_list			**token;
	int				code_err;
	struct s_xek	*x;
}	t_minishell;

typedef struct s_echo
{
	t_list	*tmp;
	char	*stockage;
	int		flag;
	int		to_free;
}	t_echo;

typedef struct s_min_max
{
	int		min;
	int		max;
}t_min_max;

typedef struct s_cd
{
	char	cwd[1024];
	char	*path;
	t_list	*tmp;
	char	*msg_err;
	char	*old_path;
	char	*home;
}	t_cd;

#endif