/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:58:32 by tas               #+#    #+#             */
/*   Updated: 2023/06/29 17:35:52 by tas              ###   ########.fr       */
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

/*
void	remove_empty_tokens(t_list **list)
{
	char		*str;
	t_list		*to_free;
	t_list		*temp;
	int			prev_flag;
	int			a;

	temp = *list;
	a = 0;
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
	printf("DEBUT: temp: [%s], flag: %d\n", temp->content, temp->flag_space);

		if (a == 1)
		{
			temp->flag_space = prev_flag;
			a = 0;	
		}
		str = temp->next->content;
		if (!str[0])
		{
			printf("---------> str: [%s]\n", str);
			a = 1;
			printf("ca rentre\n");
			to_free = temp->next;
			temp->next = temp->next->next;
	printf("to_free: [%s], flag: %d\n", to_free->content, to_free->flag_space);
		if (to_free->flag_space == 0 && temp->flag_space == 1)
			prev_flag = temp->flag_space;
		else
			prev_flag = to_free->flag_space;
		// printf("prev: %d\n", prev_flag);
	// printf("temp->: [%s], flag: %d\n", (*list)->content, to_free->flag_space);
			free(to_free->content);
			free(to_free);
		}
	printf("FIN: temp: [%s], flag: %d\n", temp->content, temp->flag_space);
		temp = temp->next;
		printf("t\n");
	}
	printf("a %d\n", prev_flag);

	if (!temp)
	{
		printf("par la\n");
		// temp = NULL;
		// temp->flag_space = prev_flag;
	}
	else if (ft_strlen(temp->content) != 0)
	{
		printf("ca sort\n");
		if (a == 0)
			temp->flag_space = prev_flag;
	}

	// if (ft_strlen(temp->content) != 0)
	// {
		// printf("ca sort\n");
		// temp->flag_space = prev_flag;
	// }
	printf("s\n");
}
*/

void remove_empty_tokens(t_list **list)
{
    char    *str;
    t_list  *to_free;
    t_list  *temp;
    int     prev_flag;
    int     a;

    temp = *list;
    a = 0;
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
        if (a == 1)
        {
            temp->flag_space = prev_flag;
            a = 0;  
        }
        str = temp->next->content;
        if (!str[0])
        {
            a = 1;
            to_free = temp->next;
            temp->next = temp->next->next;
            while (temp->next && !(temp->next->content)[0])
            {
                t_list *empty_token = temp->next;
                temp->next = temp->next->next;
                free(empty_token->content);
                free(empty_token);
            }
            if (to_free->flag_space == 0 && temp->flag_space == 1)
                prev_flag = temp->flag_space;
            else
                prev_flag = to_free->flag_space;
            free(to_free->content);
            free(to_free);
        }
        temp = temp->next;
    }
    if (temp && ft_strlen(temp->content) != 0)
    {
        if (a == 0)
            temp->flag_space = prev_flag;
    }
}

