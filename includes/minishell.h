/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:49:25 by tmejri            #+#    #+#             */
/*   Updated: 2023/03/13 11:27:06 by tas              ###   ########.fr       */
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
#include <readline/readline.h>
#include <readline/history.h>

/******************************************************************************/
/*                                  macros                                    */
/******************************************************************************/

/*Errors*/
# define ERR_REDIR_IN_OUT "syntax error near unexpected token `newline'\n"
# define ERR_QUOTE "not handle by minishell\n"

/*Quotes*/
# define QUOTE 1
# define NO_QUOTE 0


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
	struct s_list	*premier;
	char			*content;
	int				type;
	int				quote;
	struct s_list	*next;
}		t_list;




/******************************************************************************/
/*                                fonctions                                   */
/******************************************************************************/

/* builtin */
int		ft_env(char **envp);
void	ft_pwd(void);

/* exit */
int		err_msg(int n);
void	free_list(t_list **list);
void	free_all(char *s1, char *s2);

/* lexical analisis*/
char    *get_input(void);
int		is_a_separator(char c);
void    add_list(t_list **list_token, char *stockage);
char    *detect_token(char *stockage);
t_list  **create_token(t_list **list_token, char *input);

/* syntactic analisis */
void    get_type(t_list *list_token);
int		is_word(char *token);
int		determine_type(char *token);
void    substitute_dollar(t_list **list_token);
int		check_dollar(char *str);

/* redirections */
int		check_redir_in(char c);
int		check_redir_out(char c);
int		check_heredoc(char *str);

/* quoting */
int		check_pair_quote(char *str);
int		check_pair_single_quote(char *str);
int		check_pair_double_quote(char *str);
char	*word_quote(char *stockage, int quote);

/* tools list*/
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(char *input);
int		ft_lstsize(t_list *lst);
void    print_list(t_list **list_token);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void del(t_list **lst, t_list *elem);



/* tools */
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strdup_size(char *s, int size);
int		ft_strlen(char *str);
char	*ft_strjoin_mod(char *s1, char *s2, int mode);
char	**ft_split(char const *s, char c);
int		ft_strncmp(char *s1, char *s2, size_t n);

#endif