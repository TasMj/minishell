/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:11:48 by tas               #+#    #+#             */
/*   Updated: 2023/06/10 13:27:18 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

t_list	**get_list_env(char **env)
{
	int		i;
	t_list	**list_env;
	char	cwd[100];

	i = 0;
	list_env = malloc(sizeof(t_list));
	ft_memset(list_env, 0, sizeof(t_list));
	if (env[0] == NULL)
	{
		getcwd(cwd, sizeof(cwd));
		add_list(list_env, ft_strjoin("PWD=", cwd), 0);
		add_list(list_env, ft_strdup("_=/usr/bin/env"), 0);//
		return (list_env);
	}
	while (env[i] != NULL)
	{
		add_list(list_env, env[i], 0);
		i++;
	}
	return (list_env);
}

int	ft_env(t_list **l)
{
	t_list	*tmp;
	t_list	*tmp_cmd;

	tmp_cmd = *l;
	if ((*l)->next != NULL)
	{
		printf("env: ‘%s’: No such file or directory\n", (*l)->next->content);
		*l = tmp_cmd;
		return (1);
	}
	tmp = *g_list_env;
	while (*g_list_env != NULL)
	{
		printf("%s\n", (*g_list_env)->content);
		(*g_list_env) = (*g_list_env)->next;
	}
	*g_list_env = tmp;
	return (0);
}
