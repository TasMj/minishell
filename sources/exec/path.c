/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:11:54 by tas               #+#    #+#             */
/*   Updated: 2023/04/15 01:38:43 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	try_acces(char *path, char *token)
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

char	*get_command(char *token)
{
	int		i;
	int		j;
	char	*cmd;

	i = 0;
	while (token[i] && token[i] != ' ')
		i++;
	j = 0;
	cmd = malloc(sizeof(char) * i + 1);
	if (!cmd)
		return (NULL);
	while (j <= i)
	{
		cmd[j] = token[j];
		j++;
	}
	j--;
	cmd[j] = '\0';
	return (cmd);
}

char	*find_path(char **env, char *token, t_path p)
{
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

int	init_param(t_data *data, char *token, char **__environ, t_path p)
{
	data->cmd = get_command(token + extract_str(token));
	if (!data->cmd)
		return (err_msg(2));
	data->path_cmd = find_path(__environ, get_arg(data->cmd), p);
	if (!data->path_cmd)
		return (err_msg(2));
	data->token_cmd = ft_split(get_arg(token), ' ');
	if (!data->token_cmd)
		return (err_msg(2));
	return (0);
}

char	*get_arg(char *token)
{
	int	i;

	i = 0;
	if (token[i] != '/')
		return (token);
	else
	{
		i++;
		if (token[i] != 'b')
			return (NULL);
		i++;
		if (token[i] != 'i')
			return (NULL);
		i++;
		if (token[i] != 'n')
			return (NULL);
		i++;
		if (token[i] != '/')
			return (NULL);
		i++;
	}
	return (token + i);
}

