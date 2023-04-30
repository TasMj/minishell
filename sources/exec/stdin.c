/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:03:55 by tas               #+#    #+#             */
/*   Updated: 2023/04/30 21:37:12 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

int	stdin_process(t_list **list_token, char **env)
{
    t_redir     *s;
    t_list      *tmp;
    char        *c;
    
    tmp = *list_token;
    s = malloc(sizeof(t_redir));
    // c = malloc(sizeof(char) * 2);
    c = "<";
	ft_memset(s, 0, sizeof(t_redir));
    init_redir(s, list_token, env, c);
	if ((s->fd = open(s->file_name, O_RDONLY)) == -1)
    {
        printf("minishell: no such file or directory: %s\n", s->file_name);
        free_redir(s);
        free(s);
        return (1);
    }
    s->pid = fork();
    if (s->pid == -1) 
        exit(EXIT_FAILURE);
	else if (s->pid == 0)
	{
        if (dup2(s->fd, STDIN_FILENO) == -1)
            exit(EXIT_FAILURE);
		close(s->fd);
		if (execve(s->path_cmd, s->token_arg, env) == -1)
            exit(EXIT_FAILURE);
	}
    else
    {
        close(s->fd);
        if (waitpid(s->pid, NULL, 0) == -1)
            exit(EXIT_FAILURE);        
    }
    free_redir(s);
    free(s);
    (*list_token) = tmp;
	return (0);
}
