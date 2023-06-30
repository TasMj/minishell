/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:58:32 by tas               #+#    #+#             */
/*   Updated: 2023/06/30 12:28:10 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* return 1 if space or new line */
int	is_a_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

/* return 1 if space, <, <<, >, >>, | or new line */
int	is_a_separator(char c)
{
	if (is_a_space(c) == 1 || c == '|' || c == '>' || c == '<' || c == '\0')
		return (1);
	return (0);
}

char	*get_venv(char *str)
{
	t_list	*tmp;
	char	*var;
	char	*copy_env;

	tmp = *g_list_env;
	while (*g_list_env)
	{
		copy_env = del_equal((*g_list_env)->content);
		if (ft_strcmp(str, copy_env) == 0)
		{
			var = after_equal((*g_list_env)->content);
			*g_list_env = tmp;
			free(copy_env);
			return (var);
		}
		free(copy_env);
		(*g_list_env) = (*g_list_env)->next;
	}
	*g_list_env = tmp;
	return (NULL);
}

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

void    free_empty_token(t_list **list)
{
    char        *str;
    t_list        *to_free;
    t_list        *temp;

    while (*list && !((*list)->content)[0])
    {
        to_free = *list;
        *list = (*list)->next;
        free(to_free->content);
        free(to_free);
    }
    temp = *list;
    while (temp && temp->next)
    {
        str = temp->next->content;
        if (!str[0])
        {
            to_free = temp->next;
            temp->next = temp->next->next;
            free(to_free->content);
            free(to_free);
        }
        temp = temp->next;
    }
}

void remove_empty_tokens(t_list **list)
{
	t_list	*tmp;
	int		prev_flag;
	int a = 0;
	
	tmp = *list;
	while (*list)
	{
		if (a == 1 && (*list)->flag_space == 0)
		{
			(*list)->flag_space = prev_flag;
			a = 0;
		}
		if (ft_strlen((*list)->content) == 0)
		{
			a = 1;
			prev_flag = (*list)->flag_space;
		}
		(*list) = (*list)->next;
	}
	*list = tmp;
	free_empty_token(list);
}