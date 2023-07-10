/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_builtin_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:08:46 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/10 22:07:01 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_slash(char *str)
{
	int	counter;
	int	i;

	if (!str)
		return (0);
	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '/')
			counter++;
		i++;
	}
	return (counter);
}

/* return size of str until '=' */
int	ft_strlen_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] && i != '=')
		i++;
	return (i);
}

void	print_export(t_list **list)
{
	t_list	*tmp;

	tmp = (*list);
	while (*list)
	{
		printf("export %s\n", (*list)->content);
		(*list) = (*list)->next;
	}
	(*list) = tmp;
}

/* keep env variable's name */
char	*var_name(char *str)
{
	char	*stockage;
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	stockage = ft_strdup_size(str, i);
	return (stockage);
}

/* check if the variable is in the env */
int	check_var(char *str, t_minishell *data)
{
	t_list	*tmp;
	char	*var;

	tmp = *data->env;
	while (*data->env)
	{
		var = var_name((*data->env)->content);
		if (ft_strcmp(var, str) == 0)
		{
			*data->env = tmp;
			free(var);
			return (1);
		}
		free(var);
		(*data->env) = (*data->env)->next;
	}
	*data->env = tmp;
	return (0);
}
