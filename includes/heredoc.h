/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:41:00 by tas               #+#    #+#             */
/*   Updated: 2023/04/19 11:37:06 by tas              ###   ########.fr       */
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

/******************************************************************************/
/*                                fonctions                                   */
/******************************************************************************/

/* tools */
char    *get_file_name(t_list **list_token, t_redir *s, char *c);
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

#endif