/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:49:25 by tmejri            #+#    #+#             */
/*   Updated: 2023/02/22 17:29:21 by tmejri           ###   ########.fr       */
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
#include <readline/readline.h>
#include <readline/history.h>

/******************************************************************************/
/*                               structures                                   */
/******************************************************************************/

typedef struct s_list
{
	struct s_list	*premier;
	int				content;
	int				index;
	struct s_list	*next;
}		t_list;




/******************************************************************************/
/*                                fonctions                                   */
/******************************************************************************/

char	**ft_split(char *s, char c);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s);
char	**ft_split_bracket(char *s, char c);
char **all_split(char *s, char c, char d);





#endif