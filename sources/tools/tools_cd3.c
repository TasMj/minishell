/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_cd3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:15:13 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/10 22:28:02 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handl_root(t_cmd *cmd, t_cd *c, t_minishell *data)
{
	if (ft_lstsize(*cmd->cmd) == 2
		&& contain_slash((*cmd->cmd)->next->content) == 0)
	{
		chdir("/");
		*cmd->cmd = c->tmp;
		set_old_path(c->old_path, data);
		modify_pwd("/", data);
		if (c->path)
			free(c->path);
		free(c);
		return (1);
	}
	return (0);
}

int	cd_directory(t_cd *c, t_cmd *cmd, t_minishell *data)
{
	if (c->path)
		return (0);
	c->home = get_venv("HOME", data);
	if (c->home == NULL && ft_strlen((*cmd->cmd)->next->content) == 0)
	{
		return (err_msg(4, "IGNORE", 2));
	}
	if (c->home != NULL && ft_strlen((*cmd->cmd)->next->content) >= \
	ft_strlen(c->home) && ft_strncmp((*cmd->cmd)->next->content, c->home, \
	ft_strlen(c->home)) == 0)
		c->path = ft_strdup((*cmd->cmd)->next->content);
	else
		c->path = set_path(c->path, cmd->cmd);
	if (c->home)
		free(c->home);
	return (0);
}

int	go_chdir(t_cmd *cmd, t_cd *c, t_minishell *data)
{
	c->path = get_venv("HOME", data);
	if (c->path == NULL)
	{
		free(c);
		return (err_msg(4, "IGNORE", 1));
	}
	*cmd->cmd = c->tmp;
	chdir(c->path);
	set_old_path(c->old_path, data);
	modify_pwd(c->path, data);
	if (c->path)
		free(c->path);
	free(c);
	return (2);
}

int	cd_home(t_cmd *cmd, t_cd *c, t_minishell *data)
{
	if (ft_strcmp("cd", (*cmd->cmd)->content) == 0 && (*cmd->cmd)->next == NULL)
		return (go_chdir(cmd, c, data));
	else if ((*cmd->cmd)->next && ft_strcmp((".."), \
	(*cmd->cmd)->next->content) == 0)
	{
		c->path = get_previous_dir(getcwd(c->cwd, sizeof(c->cwd)));
		if (c->path == NULL)
		{
			free(c);
			g_exit_code = 127;
			err_write("cd: ..: No such file or directory\n", 2);
			return (1);
		}
	}
	else if (ft_strcmp("cd", (*cmd->cmd)->content) == 0
		&& is_in_env("HOME", data) == 0)
	{
		*cmd->cmd = c->tmp;
		free(c);
		return (err_msg(4, "IGNORE", 1));
	}
	return (0);
}

/* check if directory and not file */
int	is_dir(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (1);
	return (S_ISDIR(st.st_mode));
}
