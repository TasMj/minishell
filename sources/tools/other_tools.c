/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:12:26 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/10 23:46:37 by jthuysba         ###   ########.fr       */
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

char	*get_venv(char *str, t_minishell *data)
{
	t_list	*tmp;
	char	*var;
	char	*copy_env;

	tmp = *data->env;
	while (*data->env)
	{
		copy_env = del_equal((*data->env)->content);
		if (ft_strcmp(str, copy_env) == 0)
		{
			var = after_equal((*data->env)->content);
			*data->env = tmp;
			free(copy_env);
			return (var);
		}
		free(copy_env);
		(*data->env) = (*data->env)->next;
	}
	*data->env = tmp;
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

void	to_vomit(char *stockage)
{
	if (stockage == NULL)
		printf("\n");
	else
		printf("%s\n", stockage);
}
