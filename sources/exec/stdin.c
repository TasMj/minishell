/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:03:55 by tas               #+#    #+#             */
/*   Updated: 2023/04/16 00:48:07 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

char    *get_file_name(t_list **list_token, t_stdin *s)
{
    (void)s;
    t_list  *tmp;

    tmp = *list_token;
    while (*list_token)
    {
        if (ft_strcmp((*list_token)->content, "<") == 0 && (*list_token)->next != NULL)
            return((*list_token)->next->content);
        (*list_token) = (*list_token)->next;
    }
    (*list_token) = tmp;
    return (NULL);
}

char    *cmd_before_redir(t_list **list_token, t_stdin *s)
{
    t_list  *tmp;
    
    tmp = *list_token;
    s->cmd = "";
    while ((*list_token) && (*list_token)->type == 0)
    {
        s->cmd = ft_strjoin(s->cmd, (*list_token)->content);
        if ((*list_token)->next->type == 0)
            s->cmd = ft_strjoin(s->cmd, " ");
        (*list_token) = (*list_token)->next;
    }
    (*list_token) = tmp;
    return (s->cmd);
}


void    init_stdin(t_stdin *s, t_list **list_token, char **env)
{
    char        *args;
    t_path      p;
    t_list      *tmp;
    
    tmp = *list_token;
    s->file_name = ft_strdup_size(get_file_name(list_token, s), ft_strlen(get_file_name(list_token, s)));
    *list_token = tmp;
    args = ft_strdup_size(cmd_before_redir(list_token, s), ft_strlen(cmd_before_redir(list_token, s)));
    s->token_arg = ft_split(args, ' ');
    free(args);
    s->path_cmd = find_path(env, s->token_arg[0], p);
    *list_token = tmp;
}

int	stdin_process(t_list **list_token, char **env)
{
    t_stdin     *s;
    t_list      *tmp;
    
    tmp = *list_token;
    s = malloc(sizeof(t_stdin));
	ft_memset(s, 0, sizeof(t_stdin));
    init_stdin(s, list_token, env);
	if ((s->fd = open(s->file_name, O_RDONLY)) == -1)
    {
        printf("minishell: no such file or directory: %s\n", s->file_name);
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
    (*list_token) = tmp;
	return (0);
}