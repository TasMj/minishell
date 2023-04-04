/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:49:25 by tmejri            #+#    #+#             */
/*   Updated: 2023/04/03 13:59:15 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/******************************************************************************/
/*                                includes                                    */
/******************************************************************************/
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

/******************************************************************************/
/*                                  macros                                    */
/******************************************************************************/

/*Errors*/
# define ERR_REDIR_IN_OUT "syntax error near unexpected token `newline'\n"
# define ERR_QUOTE "not handle by minishell\n"
# define ERR_CMD "command not found\n"

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

/******************************************************************************/
/*                               structures                                   */
/******************************************************************************/

typedef struct s_list
{
	char			*content;
	int				type;
	struct s_list	*next;
}		t_list;

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	pid_t	pid;
	char	*cmd;
	char	*path_cmd;
	char	**token_cmd;
}t_pipex;

typedef struct s_path
{
	int		i;
	int		j;
	char	*path_with_points;
	char	*path_without;
	char	**path_split;
}t_path;


/******************************************************************************/
/*                                fonctions                                   */
/******************************************************************************/

/***** PARSING *****/

/* builtin */
int		ft_env(char **envp);
void	ft_pwd(void);

/* exit */
int		err_msg(int n);
void	free_list(t_list **list);
void	free_tab(char **tab);
void	free_all(char *s1, char *s2);

/* create token */
char    *get_input(void);
int		is_a_space(char c);
void    add_list(t_list **list_token, char *stockage);
t_list  **create_token(t_list **list_token, char *input);

/* quotes */
int		check_pair_quote(char *str);
int		check_pair_single_quote(char *str);
int		check_pair_double_quote(char *str);
char	*word_quote(char *stockage, int quote);
char    *remove_quotes(char *str);
void    remove_list_quotes(t_list **list_token);

/* redirections */
int		check_redir_in(char c);
int		check_redir_out(char c);
int		check_heredoc(char *str);
int		check_append(char *str);

/* substitution */
int		check_dollar(char *str);
char    *remove_space(char *str);
char    *substitution(char *token);
void    substitute_dollar(t_list **list_token);
char    *sub_quotes(char *token);

/* type */
int		determine_type(char *token);
void    get_type(t_list **list_token);

/* tools list*/
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(char *input);
void    print_list(t_list **list);

/* tools */
char	**ft_split(char const *s, char c);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strdup_size(char *s, int size);
int		ft_strlen(char *str);
char	*ft_strjoin_mod(char *s1, char *s2, int mode);
int		ft_strncmp(char *s1, char *s2, size_t n);

/***** EXEC *****/

/* path*/
int		try_acces(char *path, char *token);
char	*get_command(char *token);
char	*find_path(char **env, char *token, t_path p);
int		init_param(t_pipex *pipex, char *token, char **__environ, t_path p);
char	*get_arg(char *token);

/* prcess */
int		is_executable(char *token);
int		creating_child_process(t_list **list_token, char ** envp);
int		child_process(t_pipex *pipex, char **__environ);
int		extract_str(char *str);

/* type process */
int		word_process(t_list *list_token, t_pipex *pipex, char **env, t_path path);


#endif