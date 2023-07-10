/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_cd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:13:13 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/10 19:59:00 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dir_err(t_cmd *cmd, char *path)
{
	char	*msg_err;

	msg_err = ft_strdup("cd: ");
	msg_err = ft_strjoin_mod(msg_err, (*cmd->cmd)->next->content, 1);
	msg_err = ft_strjoin_mod(msg_err, ": Not a directory\n", 1);
	err_write(msg_err, 2);
	g_exit_code = 127;
	free(msg_err);
	free(path);
}

void	chdir_err(t_cmd *cmd, char *path)
{
	char	*msg_err;

	msg_err = ft_strdup("cd: ");
	msg_err = ft_strjoin_mod(msg_err, (*cmd->cmd)->next->content, 1);
	msg_err = ft_strjoin_mod(msg_err, ": No such file or directory\n", 1);
	err_write(msg_err, 2);
	g_exit_code = 1;
	free(msg_err);
	free(path);
}

/* return if not a file or a directory */
int	err_cd(t_cmd *cmd, char *path)
{
	if (path == NULL)
	{
		g_exit_code = 127;
		err_write("cd: ..: No such file or directory\n", 2);
		free(path);
		return (1);
	}
	if (is_dir(path) == 0)
	{
		dir_err(cmd, path);
		return (1);
	}
	if (chdir(path) == -1)
	{
		chdir_err(cmd, path);
		return (1);
	}
	return (0);
}

/* return path */
char	*set_path(char *path, t_list **list)
{
	char	cwd[1024];

	path = ft_strdup((getcwd(cwd, sizeof(cwd))));
	path = ft_strjoin_mod(path, "/", 1);
	path = ft_strjoin_mod(path, (*list)->next->content, 1);
	return (path);
}

int	err_nb_cmd(t_cmd *cmd, char *path)
{
	if (cmd->data->x->nb_cmd > 1)
	{
		path = ft_strdup((*cmd->cmd)->next->content);
		if (is_dir(path) == 0)
		{
			put_str_err("cd: ");
			put_str_err((*cmd->cmd)->next->content);
			put_str_err(": Not a directory\n");
			g_exit_code = 127;
		}
		return (free(path), 1);
	}
	return (0);
}
