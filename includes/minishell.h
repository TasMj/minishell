/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:49:25 by tmejri            #+#    #+#             */
/*   Updated: 2023/03/03 12:51:56 by tas              ###   ########.fr       */
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
#include <readline/readline.h>
#include <readline/history.h>

/******************************************************************************/
/*                                  macros                                    */
/******************************************************************************/

/*Errors*/
# define ERR_REDIR_IN_OUT "syntax error near unexpected token `newline'\n"
# define ERR_QUOTE "+ tard return '>' plus boucle infini qui recup les input jusqu'a un ctrlD ou ctrlC"

/******************************************************************************/
/*                                   enum                                     */
/******************************************************************************/

enum token_type {
	WORD,
	VAR,
	PIPE,
	HEREDOC	
};


/******************************************************************************/
/*                               structures                                   */
/******************************************************************************/

typedef struct s_list
{
	struct s_list	*premier;
	char			*content;
	char			*type;
	// int				index;
	struct s_list	*next;
}		t_list;




/******************************************************************************/
/*                                fonctions                                   */
/******************************************************************************/

/* exit */
int		err_msg(int n);
void	free_list(t_list **list);

/* lexical analisis*/
char    *get_input(void);
int		is_a_separator(char c);
void    add_list(t_list **list_token, char *stockage);
char    *detect_token(char *stockage);
void    create_token(t_list **list_token, char *input);

/* check_args */
int		check_redir_in(char c);
int		check_redir_out(char c);
int		check_redir_in_out(char *str);
int		check_args(char *str);

/* quoting */
int		is_a_quoting(char c);
int		check_pair_single_quote(char *str);
int		check_pair_double_quote(char *str);
char	*word_quote(char *stockage, int quote);

/* tools list*/
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(t_list *new, char *input);
int		ft_lstsize(t_list *lst);
void    print_list(t_list **list_token);

/* tools */
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strdup_size(char *s, int size);
int		ft_strlen(char *str);


#endif