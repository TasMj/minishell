/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:49:25 by tmejri            #+#    #+#             */
/*   Updated: 2023/05/28 19:59:39 by jthuysba         ###   ########.fr       */
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
# define ERR_MANY_ARG "too many arguments (WIP)\n"
# define ERR_HOME "HOME not set\n"
# define ERR_EXPORT "not a valid identifier\n"

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
	int				index;
	int				flag_space;
	int				flag_quote;
	struct s_list	*next;
}	t_list;

typedef struct s_substitution
{
    char    *var_substitute;
    char    *keep_var;
    char	*keep_var2;
    char    *new_content;
    char    *without_dollar;
    char	*stock;
    int		start;
    int		end;
    int		deb;
    int		i;
	int		flag;
	int		flag_space;
	int		flag_keep_quote;
	int		quote;
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

typedef struct s_exec
{
	t_list	**token;
	// t_cmd	*cmd;
	char	**env;
	int		**fd;
	int		nb_pipes;
	int		nb_cmd;
}	t_exec;

typedef struct s_cmd
{
	int		id;
	t_list	**token;
	t_list	**cmd;
	char	**tab;
	char	*path;
	int		*redir;
	char	**file;
	int		nb_redir;
}	t_cmd;

typedef struct s_xek
{
	t_cmd	*cmd;
	int		nb_cmd;
}	t_xek;

typedef struct s_minishell
{
	char	*input;
	t_list	**token;
	struct s_xek	*x;
}	t_minishell;

/******************************************************************************/
/*                                fonctions                                   */
/******************************************************************************/

/***** PARSING *****/

/* builtin */
int 	ft_echo(t_list **list_token);
int 	ft_env(t_list **list_cmd);
void	ft_pwd(void);
int 	ft_unset(t_list **list_token);
int 	ft_cd(t_list **list_token);
int 	ft_export(t_list **list_token);
void	ft_exit(t_list **lst);

/* exit */
int		err_msg(int n);
void	free_list(t_list **list);
void	free_tab(char **tab);
void	free_all(char *s1, char *s2);
void	free_data(t_data *data);

/* create token */
char    *get_input(void);
int		is_a_space(char c);
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
char    *sub_quotes(char *token, t_substitution *s);

/* type */
int		determine_type(char *token);
void    get_type(t_list **list_token);

/* tools list*/
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(char *input, int flag_space);
void    add_list(t_list **list_token, char *stockage, int flag_space);
void    print_list(t_list **list);
int		ft_lstsize(t_list *lst);

/* tools */
char	**ft_split(char const *s, char c);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strdup(char *s);
char	*ft_strdup_size(char *s, int size);
int		ft_strlen(char *str);
char	*ft_strjoin_mod(char *s1, char *s2, int mode);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
int		is_a_space(char c);
int		is_a_separator(char c);
int    init_list(t_list **list_token, char *input);

/***** EXEC *****/

/* path*/
int		try_acces(char *path, char *token);
char	*get_command(char *token);
char	*find_path(char **env, char *token);
int		init_param(t_data *data, char *token, char **__environ);
char	*get_arg(char *token);

/* process */
int		extract_str(char *str);

/* exec all */
int	exec_all(t_exec *data);
char	**lst_to_tab(t_list **lst);
int	is_heredoc(t_cmd *cmd);

/* setup cmd */
t_list	**get_cmd(t_list *token);

/* setup pipes */
int		count_pipes(t_list *token);
void	setup_pipes(t_exec *data);
int		nb_cmd(t_list *token);

/* set fd */
int	set_fd(t_cmd *cmd, t_list *token);

/* clean all */
void	close_all(t_exec *data, int end);
void	clean_all(t_exec *data);

/* exec god */
int		exec(t_list **token, t_list **env);
int		exec_builtin(t_list **list_token);

/* exec builtins */
int	fork_builtin(t_cmd *cmd, t_exec *data);
int	simple_builtin(t_cmd *cmd, t_exec *data);
int	is_builtin(t_list **cmd);

char	*del_equal(char *str);
void    reunite_token(t_list **list_token);



/* we exec */
int		we_exec(t_minishell *data);
int		prep_cmd(t_minishell *data);
int		nb_cmd(t_list *token);
void	set_to_zero(t_xek *x);
int		nb_redir(t_list	*elem);


#endif