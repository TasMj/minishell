/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:49:25 by tmejri            #+#    #+#             */
/*   Updated: 2023/06/26 17:22:23 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

/******************************************************************************/
/*                                includes                                    */
/******************************************************************************/

/* library */
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

/* headers */
# include "struct.h"
# include "builtin.h"
# include "exec.h"
# include "exit.h"
# include "parsing.h"
# include "tools.h"

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

#endif