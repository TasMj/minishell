/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:49:25 by tmejri            #+#    #+#             */
/*   Updated: 2023/02/27 13:58:48 by tas              ###   ########.fr       */
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
/*                                  macros                                    */
/******************************************************************************/

enum token_type {
	WORD,
	FLAG	
};


/******************************************************************************/
/*                               structures                                   */
/******************************************************************************/

typedef struct s_list
{
	struct s_list	*premier;
	char			*type;
	int				index;
	struct s_list	*next;
}		t_list;




/******************************************************************************/
/*                                fonctions                                   */
/******************************************************************************/

size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
char    *get_input(void);
int check_args(char *str);
int check_peer_quote(char *str);

int	err_msg(int n);


#endif