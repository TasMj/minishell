/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:34:23 by tas               #+#    #+#             */
/*   Updated: 2023/04/15 19:53:02 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

char    *cmd_before_heredoc(t_list **list_token, t_heredoc *h)
{
    t_list  *tmp;
    
    tmp = *list_token;
    h->cmd = "";
    while ((*list_token) && (*list_token)->type == 0)
    {
        h->cmd = ft_strjoin(h->cmd, (*list_token)->content);
        if ((*list_token)->next->type == 0)
            h->cmd = ft_strjoin(h->cmd, " ");
        (*list_token) = (*list_token)->next;
    }
    (*list_token) = tmp;
    return (h->cmd);
}

int heredoc(t_list **list_token, char **env)
{
    t_heredoc   *h;
    t_list      *first_cmd;
    t_path      p;
    char        *args;
    
    h = malloc(sizeof(t_heredoc));
    first_cmd = *list_token;
    args = ft_strdup_size(cmd_before_heredoc(list_token, h), ft_strlen(cmd_before_heredoc(list_token, h)));
    while (*list_token)
    {
        if (check_heredoc((*list_token)->content) == 1 && (*list_token)->next == NULL)
            return (1);
        else if (check_heredoc((*list_token)->content) == 1)
        {
            h->path_cmd = find_path(env, first_cmd->content, p);
            h->token_arg = ft_split(args, ' ');
            h->delimineur = ft_strdup_size((*list_token)->next->content, ft_strlen((*list_token)->next->content));
            heredoc_process(h);
        }
        (*list_token) = (*list_token)->next;
    }
    (*list_token) = first_cmd;
    return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	char	*ss1;
	char	*ss2;
	int		i;

	ss1 = s1;
	ss2 = s2;
	i = 0;
    if (ft_strlen(ss1) != ft_strlen(ss2))
        return (1);
    else
    {
	    while (i < ft_strlen(ss1))
	    {
	    	if (ss1[i] == ss2[i])
	    		i++;
	    	else
	    		return (1);
	    }
    }
	return (0);
}

int	heredoc_process(t_heredoc *h)
{
    char    *stockage;

    if (pipe(h->tube) == -1)
        exit(EXIT_FAILURE);
    h->pid = fork();
    if (h->pid == -1) 
        exit(EXIT_FAILURE);
    if (h->pid == 0) 
    {
        close(h->tube[0]);
        while (1) 
        {
            stockage = readline("heredoc> ");
            if (ft_strcmp(stockage, h->delimineur) == 0)
                break;
            if (write(h->tube[1], ft_strjoin(stockage, "\n"), ft_strlen(stockage) + 1) == -1) 
                exit(EXIT_FAILURE);
            free(stockage);
        }
        close(h->tube[1]);
        exit(EXIT_SUCCESS);
    }
    else 
    {
        close(h->tube[1]);
        if (waitpid(h->pid, NULL, 0) == -1)
            exit(EXIT_FAILURE);
        dup2(h->tube[0], STDIN_FILENO);
        char *envp[] = { NULL };
        if (execve(h->path_cmd, h->token_arg, envp) == -1) 
            exit(EXIT_FAILURE);
        close(h->tube[0]);
        exit(EXIT_SUCCESS);
    }
    return 0;
}
