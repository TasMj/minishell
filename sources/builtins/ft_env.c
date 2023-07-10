/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:11:48 by tas               #+#    #+#             */
/*   Updated: 2023/07/10 22:03:12 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* initialisation of the environnement. Create a small env if env -i */
t_list	**get_list_env(char **env)
{
	int		i;
	t_list	**list_env;
	char	cwd[100];

	i = 0;
	list_env = malloc(sizeof(t_list));
	if (!list_env)
		return (NULL);
	ft_memset(list_env, 0, sizeof(t_list));
	if (env[0] == NULL)
	{
		getcwd(cwd, sizeof(cwd));
		add_list(list_env, ft_strjoin("PWD=", cwd), 0);
		add_list(list_env, ft_strdup("_=/usr/bin/env"), 0);
		return (list_env);
	}
	while (env[i] != NULL)
	{
		add_list(list_env, ft_strdup(env[i]), 0);
		i++;
	}
	return (list_env);
}

int	ft_env(t_list **l, t_minishell *data)
{
	t_list	*tmp;
	t_list	*tmp_cmd;

	tmp_cmd = *l;
	if ((*l)->next != NULL)
	{
		err_write("env: No such file or directory\n", 1);
		*l = tmp_cmd;
		return (1);
	}
	tmp = *data->env;
	while (*data->env != NULL)
	{
		printf("%s\n", (*data->env)->content);
		(*data->env) = (*data->env)->next;
	}
	*data->env = tmp;
	return (0);
}
