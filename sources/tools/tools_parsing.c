/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:58:32 by tas               #+#    #+#             */
/*   Updated: 2023/05/28 00:49:17 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

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

void	remove_empty_tokens(t_list **list)
{
	char		*str;
	t_list		*to_free;
	t_list		*temp;

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

char	*get_venv(char *str)
{
	t_list	*tmp;
	char	*var;
	char	*copy_env;

	tmp = *g_list_env;
	while (*g_list_env)
	{
		copy_env = ft_strdup((*g_list_env)->content);
		if (ft_strcmp(str, del_equal(copy_env)) == 0)
		{
			var = ft_strdup(after_equal((*g_list_env)->content)); //
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
