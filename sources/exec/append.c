/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:56:40 by tas               #+#    #+#             */
/*   Updated: 2023/04/30 15:31:54 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

int append_process(t_list **list_token, char **env)
{
    t_redir     *a;
    t_list      *tmp;
    char        buffer[1024];
    int         n;

    tmp = *list_token;
    a = malloc(sizeof(t_redir));
	ft_memset(a, 0, sizeof(t_redir));
    init_redir(a, list_token, env, ">>");
    if (pipe(a->tube) == -1)
        exit(EXIT_FAILURE);
    a->pid = fork();
    if (a->pid == -1)
        exit(EXIT_FAILURE);
    else if (a->pid == 0) 
    {
        if (dup2(a->tube[1], STDOUT_FILENO) == -1)
            exit(EXIT_FAILURE);
        close(a->tube[0]);
   		execve(a->path_cmd, a->token_arg, env);
    }
    else
    {
        a->fd = open(a->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (a->fd == -1)
            exit(EXIT_FAILURE);
        if (dup2(a->tube[0], STDIN_FILENO) == -1)
            exit(EXIT_FAILURE);
        close(a->tube[1]);
        if (waitpid(a->pid, NULL, 0) == -1)
            exit(EXIT_FAILURE);
        while ((n = read(a->tube[0], buffer, sizeof(buffer))) > 0) 
        {
            if (write(a->fd, buffer, n) == -1)
                exit(EXIT_FAILURE);
        }
        close(a->fd);
        close(a->tube[0]);
    }
    free_redir(a);
    (*list_token) = tmp;
    return 0;
}
