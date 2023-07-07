/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:12:26 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/06 02:13:17 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extract_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
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

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ' || c == '\0')
		return (1);
	else
		return (0);
}

int	space_only(char *p)
{
	char	*char_ptr;

	char_ptr = p;
	if (char_ptr != NULL)
	{
		while (*char_ptr)
		{
			if (ft_isspace(*char_ptr))
				char_ptr++;
			else
				return (0);
		}
		return (1);
	}
	else
		return (1);
}
