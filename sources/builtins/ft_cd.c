/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:10:00 by tas               #+#    #+#             */
/*   Updated: 2023/05/19 15:48:42 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

/*verifier qu'il s'agit d'un dossier et pas un fichier*/
int is_dir(char *path)
{
    struct  stat st;
    if (stat(path, &st) == -1)
        return (1);
    return (S_ISDIR(st.st_mode));
}

int count_slash(char *str)
{
    int counter;
    int i;

    i = 0;
    counter = 0;
    while(str[i])
    {
        if (str[i] == '/')
            counter++;
        i++;
    }
    return (counter);
}

char    *get_previous_dir(char *str)
{
    int i;
    int slash;

    i = 0;
    slash = count_slash(str);
    while (str[i] && slash > 0)
    {
        if (str[i] == '/')
            slash--;
        i++;
    }
    return (ft_strdup_size(str, i));
}

int ft_cd(t_list **list_token)
{
    char    cwd[1024];
    char    *path;
    t_list  *tmp;

    tmp = *list_token;
    if (ft_strcmp("cd", (*list_token)->content) == 0 && (*list_token)->next == NULL)
        path = ft_strdup_size(getenv("HOME"), ft_strlen(getenv("HOME")));
    else if ((*list_token)->next && ft_strcmp((".."), (*list_token)->next->content) == 0)
    {
        if (ft_lstsize(*list_token) >= 3)
            return (err_msg(3));
        path = get_previous_dir(getcwd(cwd, sizeof(cwd)));
    }
    else
    {
        if (ft_lstsize(*list_token) > 2)
            return (err_msg(3));
        path = ft_strdup_size((getcwd(cwd, sizeof(cwd))), ft_strlen(getcwd(cwd, sizeof(cwd))));
        path = ft_strjoin(path, "/");
        path = ft_strjoin(path, (*list_token)->next->content);
    }
    if (is_dir(path) == 0)
    {
        printf("minishell: cd: %s: Not a directory\n", (*list_token)->next->content);
        free(path);
        return (1);
    }
    if (chdir(path) == -1)
    {
        printf("minishell: cd: %s: No such file or directory\n", (*list_token)->next->content);
        free(path);
        return (1);
    }
    free(path);
    *list_token = tmp;
    return (0);
}
