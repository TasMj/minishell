/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:11:23 by tas               #+#    #+#             */
/*   Updated: 2023/05/19 15:26:17 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

t_list	**list_ENVI;

int check_equal(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

char    *take_off_equal(char *str)
{
    int     i;
    char    *var;
    
    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    var = ft_strdup_size(str, i);
    return (var);
}

int is_in_env(char *str)
{
    t_list  *tmp;

    tmp = *list_ENVI;
    while (*list_ENVI)
    {
        if (ft_strcmp(str, take_off_equal((*list_ENVI)->content)) == 0)
            return (1);
        (*list_ENVI) = (*list_ENVI)->next;
    }
    *list_ENVI = tmp;
    return (0);
}

t_list  **ft_copy_list(t_list  **copy)
{
    while (*list_ENVI)
    {
        add_list(copy, (*list_ENVI)->content, 0);
        (*list_ENVI) = (*list_ENVI)->next;
    }
    return (copy);
}

/* return taill de str jusau'a = */
int	ft_strlen_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] && i != '=')
		i++;
	return (i);
}

int is_sorted(t_list **list)
{
    t_list  *tmp;
    int     min;
    int     max;

    (void)min;
    (void)max;
    
    min = 0;
    max = 0;
    tmp = *list;
    while ((*list)->next != NULL)
    {
        if (ft_strlen_var((*list)->content) >= ft_strlen_var((*list)->next->content))
        {
            min = ft_strlen_var((*list)->next->content);
            max = ft_strlen_var((*list)->content);
        }
        else
        {
            min = ft_strlen_var((*list)->content);
            max = ft_strlen_var((*list)->next->content);
        }
        if (ft_strncmp((*list)->content, (*list)->next->content, min) > 0)
            return (1);
        (*list) = (*list)->next;
    }
    *list = tmp;
    return (0);    
}

t_list  **sort_env(t_list **list)
{
    t_list  *tmp;
    int     min;
    int     max;

    char  *tmp1;
    char  *tmp2;

    (void)min;
    (void)max;
    
    min = 0;
    max = 0;
    tmp = *list;
    while (is_sorted(list) == 1)
    {
        if (ft_strlen_var((*list)->content) >= ft_strlen_var((*list)->next->content))
        {
            min = ft_strlen_var((*list)->next->content);
            max = ft_strlen_var((*list)->content);
        }
        else
        {
            min = ft_strlen_var((*list)->content);
            max = ft_strlen_var((*list)->next->content);
        }
        if (ft_strncmp((*list)->content, (*list)->next->content, min) > 0)
        {
            tmp1 = ft_strdup_size((*list)->content, ft_strlen((*list)->content));
            tmp2 = ft_strdup_size((*list)->next->content, ft_strlen((*list)->next->content));
            (*list)->content = ft_strdup_size(tmp2, ft_strlen(tmp2));
            (*list)->next->content = ft_strdup_size(tmp1, ft_strlen(tmp1));
            free(tmp1);
            free(tmp2);
            *list = tmp;
        }
        (*list) = (*list)->next;
    }
    *list = tmp;
    return (list);
}

void	print_export(t_list **list)
{
	t_list *tmp;

	tmp = (*list);
	while (*list)
	{
		printf("export %s\n", (*list)->content);
		(*list) = (*list)->next;
	}
	(*list) = tmp;
}

int sort_env_ascii(void)
{
    t_list  **copy;

    copy = malloc(sizeof(t_list));
    ft_memset(copy, 0, sizeof(t_list));
    copy = ft_copy_list(copy);
    copy = sort_env(copy);
    print_export(copy);
    return (0);
}

int ft_export(t_list **list_token)
{
    t_list  *tmp;
    char    *add_env;
    
    tmp = *list_ENVI;
    if (ft_lstsize(*list_token) == 1)
        sort_env_ascii();
    else
    {
        while (*list_token != NULL)
        {
            (*list_token) = (*list_token)->next;
            if (check_equal((*list_token)->content) == 1)
            {
                if (is_in_env(take_off_equal((*list_token)->content)) == 0)
                {
                    add_env = ft_strdup_size((*list_token)->content, ft_strlen((*list_token)->content));
                    while ((*list_token)->next != NULL && (*list_token)->flag_space != 1)
                    {
                        printf("content: %s, %d\n", (*list_token)->content, (*list_token)->flag_space);
                        (*list_token) = (*list_token)->next;
                        add_env = ft_strjoin_mod(add_env, (*list_token)->content, 0);
                    }
                    add_list(list_ENVI, add_env, 0);
                    *list_ENVI = tmp;
                    return (0);
                }
                else
                {
                    while (*list_ENVI)
                    {
                        if (ft_strcmp(take_off_equal((*list_ENVI)->content), take_off_equal((*list_token)->content)) == 1)
                            (*list_ENVI) = (*list_ENVI)->next;
                        else if (ft_strcmp(take_off_equal((*list_ENVI)->content), take_off_equal((*list_token)->content)) == 0)
                        {
                            (*list_ENVI)->content = ft_strdup_size((*list_token)->content, ft_strlen((*list_token)->content));
                            while ((*list_token)->next != NULL && (*list_token)->next->flag_space != 1)
                            {
                                (*list_token) = (*list_token)->next;
                                (*list_ENVI)->content = ft_strjoin_mod((*list_ENVI)->content, (*list_token)->content, 0);
                            }
                            *list_ENVI = tmp;
                            return (0);
                        }
                    }
                }
            }
            (*list_token) = (*list_token)->next;
        }        
    }
    *list_ENVI = tmp;
    return (0);
}

