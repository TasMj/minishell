/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 23:06:38 by tas               #+#    #+#             */
/*   Updated: 2023/05/16 17:44:26 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

int	stdout_process(t_list **list_token, char **env)
{    
    t_redir     *s;
    t_list      *tmp;
    char        *c;
    
    tmp = *list_token;
    s = malloc(sizeof(t_redir));
    // c = malloc(sizeof(char) * 2);
    c = ">";
	ft_memset(s, 0, sizeof(t_redir));
    init_redir(s, list_token, env, c);
    if (pipe(s->tube) == -1)
        exit(EXIT_FAILURE);
    s->pid = fork();
    if (s->pid == -1)
        exit(EXIT_FAILURE);
    else if (s->pid == 0) 
    {
        close(s->tube[0]);
        dup2(s->tube[1], STDOUT_FILENO);
        close(s->tube[1]);
		if (execve(s->path_cmd, s->token_arg, env) == -1)
        {
            free_redir(s);
            return (1);
        }
    } 
    else 
    {
        close(s->tube[1]);
        waitpid(s->pid, NULL, 0);
        int fd_out = open(s->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(s->tube[0], STDIN_FILENO);
        dup2(fd_out, STDOUT_FILENO);
        close(s->tube[0]);
		if (execve(s->path_cmd, s->token_arg, env) == -1)
        {
            free_redir(s);
            return (1);
        }
    }
    free_redir(s);
    (*list_token) = tmp;
    return (0);
}
