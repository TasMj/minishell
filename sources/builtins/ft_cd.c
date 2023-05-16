/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:10:00 by tas               #+#    #+#             */
/*   Updated: 2023/04/30 13:27:45 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

/* TO DO
-check si besoin de malloc input
-msg d'err si ni file ni directory, si file et pas directory
*/

/* recup repertoire */
char    *get_new_dir()
{
    t_list  **list_cmd;
    t_list  *tmp;
    
    list_cmd = malloc(sizeof(t_list));
    list_cmd[0] = NULL;
    list_cmd = get_list_input(list_cmd);
    tmp = *list_cmd;
    if(ft_strncmp((*list_cmd)->content, "cd", 2) == 0 && (*list_cmd)->next)
        return ((*list_cmd)->next->content);
    return (tmp->content);
}

//verifier qu'il s'agit d'un doss et pas un fichier
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

int ft_cd()
{
    char    *input;
    char    *arg;
    char    cwd[1024];
    char    *path;
    
    ft_pwd();

    input = get_new_dir();
    arg = ft_strdup_size(input, ft_strlen(input));
    if (ft_strcmp("cd", arg) == 0)
        path = ft_strdup_size(getenv("HOME"), ft_strlen(getenv("HOME")));
    else if (ft_strcmp((".."), arg) == 0)
        path = get_previous_dir(getcwd(cwd, sizeof(cwd)));
    else
    {
        path = ft_strdup_size((getcwd(cwd, sizeof(cwd))), ft_strlen(getcwd(cwd, sizeof(cwd))));
        path = ft_strjoin(path, "/");
        path = ft_strjoin(path, arg);
    }
    if (chdir(path) == -1)
    {
        printf("cd: no such file or directory: %s\n", input);
        free(input);
        free(arg);
        free(path);
        return (1);
    }
    if (is_dir(path) == 0)
    {
        printf("cd: not a directory: %s\n", path);
        free(input);
        free(arg);
        free(path);
        return (1);
    }
    ft_pwd();
    free(input);
    free(arg);
    free(path);
    return (0);
}

// int main(int argc, char **argv, char **env)
// {
    // (void)argc;
    // (void)argv;
    // (void)env;
    // 
    // ft_cd();
    // return (0);
// }