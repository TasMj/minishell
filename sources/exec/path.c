/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:11:54 by tas               #+#    #+#             */
/*   Updated: 2023/06/23 12:32:02 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	try_acces(char *path, char *token)
{
	char	*s;

	s = ft_strjoin_mod(path, "/", 0);
	s = ft_strjoin_mod(s, token, 1);
	if (access(s, F_OK | X_OK) == 0)
	{
		free(s);
		return (0);
	}
	free(s);
	return (1);
}

char	*find_path(char **env, char *token)
{
	t_path	p;

	ft_memset(&p, 0, sizeof(t_path));
	p.i = 0;
	p.j = 0;
	while (env[p.i] && token)
	{
		if (ft_strncmp(env[p.i], "PATH=", 5) == 0)
		{
			p.path_with_points = env[p.i] + 5;
			p.path_split = ft_split(p.path_with_points, ':');
			while (p.path_split[p.j])
			{
				if (try_acces(p.path_split[p.j], token) == 0)
				{
					p.path_without = ft_strjoin_mod(p.path_split[p.j], "/", 0);
					p.path_without = ft_strjoin_mod(p.path_without, token, 1);
					free_tab(p.path_split);
					return (p.path_without);
				}
				p.j++;
			}
		}
		p.i++;
	}
	free_tab(p.path_split);
	return (NULL);
}
