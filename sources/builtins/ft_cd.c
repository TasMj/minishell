/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:10:00 by tas               #+#    #+#             */
/*   Updated: 2023/07/05 20:28:53 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* keep the last pwd */
static int	set_old_path(char *path)
{
	t_list	*tmp;
	char	*copy_env;

	if (is_in_env("OLDPWD") == 0)
		return (1);
	tmp = *g_list_env;
	while (*g_list_env)
	{
		copy_env = del_equal((*g_list_env)->content);
		if (ft_strcmp(copy_env, "OLDPWD") == 1)
			(*g_list_env) = (*g_list_env)->next;
		else if (ft_strcmp(copy_env, "OLDPWD") == 0)
		{
			free((*g_list_env)->content);
			(*g_list_env)->content = ft_strjoin("OLDPWD=", path);
			*g_list_env = tmp;
			free(copy_env);
			return (0);
		}
		free(copy_env);
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

/* return the previous directory */
static char	*get_previous_dir(char *str)
{
	int	i;
	int	slash;

	i = 0;
	slash = count_slash(str);
	if (count_slash(str) == 0)
		return (str);
	while (str[i] && slash > 0)
	{
		if (str[i] == '/')
			slash--;
		i++;
	}
	return (ft_strdup_size(str, i));
}

void	dir_err(t_cmd *cmd, char *path)
{
	char *msg_err;
	
	msg_err = ft_strdup("cd: ");
	msg_err = ft_strjoin_mod(msg_err, (*cmd->cmd)->next->content, 1);
	msg_err = ft_strjoin_mod(msg_err, ": Not a directory\n", 1);
	err_write(msg_err, 2);
	cmd->data->code_err = 127;
	free(msg_err);
	free(path);
}

void	chdir_err(t_cmd *cmd, char *path)
{
	char *msg_err;
	
	msg_err = ft_strdup("cd: ");
	msg_err = ft_strjoin_mod(msg_err, (*cmd->cmd)->next->content, 1);
	msg_err = ft_strjoin_mod(msg_err, ": No such file or directory\n", 1);
	err_write(msg_err, 2);
	cmd->data->code_err = 127;
	free(msg_err);
	free(path);
}

/* return if not a file or a directory */
static int	err_cd(t_cmd *cmd, char *path)
{
	if (path == NULL)
	{
		cmd->data->code_err = 127;
		err_write("cd: ..: No such file or directory\n", 2);
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
static char	*set_path(char *path, t_list **list)
{
	char	cwd[1024];
	
	path = ft_strdup((getcwd(cwd, sizeof(cwd))));
	path = ft_strjoin_mod(path, "/", 1);
	path = ft_strjoin_mod(path, (*list)->next->content, 1);
	return (path);
}

static int	modify_pwd(char *new_pwd)
{
	char	*copy_env;
	t_list	*tmp;

	tmp = *g_list_env;
	while (*g_list_env)
	{
		copy_env = del_equal((*g_list_env)->content);
		if (ft_strcmp(copy_env, "PWD") == 1)
			(*g_list_env) = (*g_list_env)->next;
		else if (ft_strcmp(copy_env, "PWD") == 0)
		{
			free((*g_list_env)->content);
			(*g_list_env)->content = ft_strjoin("PWD=", new_pwd);
			*g_list_env = tmp;
			free(copy_env);
			return (1);
		}
		free(copy_env);
	}
	*g_list_env = tmp;
	return (0);
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
            cmd->data->code_err = 127;
        }
        return (free(path), 1);
    }
	return (0);
}

int	handl_root(t_cmd *cmd, t_cd *c)
{
	if (ft_lstsize(*cmd->cmd) == 2 && contain_slash((*cmd->cmd)->next->content) == 0)
	{
		chdir("/");
		*cmd->cmd = c->tmp;
		if (c->path)
			free(c->path);
		set_old_path(c->old_path);
		modify_pwd("/");
		return (0);
	}
	return (1);
}

int	cd_directory(t_cd *c, t_cmd *cmd)
{
	c->home = get_venv("HOME");
	if (c->home == NULL && ft_strlen((*cmd->cmd)->next->content) == 0)
		return (err_msg(4, "IGNORE", 2));
	if (c->home != NULL && ft_strlen((*cmd->cmd)->next->content) >= ft_strlen(c->home) && ft_strncmp((*cmd->cmd)->next->content, c->home, ft_strlen(c->home)) == 0)
		c->path = ft_strdup((*cmd->cmd)->next->content);
	else
		c->path = set_path(c->path, cmd->cmd);
	if (c->home)
		free(c->home);
	return (0);
}

int	cd_list_one_tok(t_cmd *cmd, t_cd *c)
{
	if (handl_root(cmd, c) == 0)
		return (0);
	else if (ft_lstsize(*cmd->cmd) == 2 && (*cmd->cmd)->next->content[0] == '-')
	{
		if (ft_strlen((*cmd->cmd)->next->content) == 1)
			c->path = get_venv("OLDPWD");
		else
		{
			c->msg_err = ft_strjoin("cd: ", (*cmd->cmd)->next->content);
			c->msg_err = ft_strjoin_mod(c->msg_err, ": invalid option\ncd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n", 1);
			err_write(c->msg_err, 2);
			free(c->msg_err);
			return (1);
		}
	}
	else if (ft_lstsize(*cmd->cmd) == 2 && (*cmd->cmd)->next->content[0] == '~')
	{
		if (is_in_env("HOME") == 0)
			return (err_msg(4, "IGNORE", 2));
		c->path = get_venv("HOME");
	}
	else
		cd_directory(c, cmd);
	return (0);
}

int	cd_home(t_cmd *cmd, t_cd *c)
{
	if (ft_strcmp("cd", (*cmd->cmd)->content) == 0 && (*cmd->cmd)->next == NULL)
	{
		c->path = get_venv("HOME");
		if (c->path == NULL)
			return (err_msg(4, "IGNORE", 1));
		*cmd->cmd = c->tmp;
		chdir(c->path);
		set_old_path(c->old_path);
		modify_pwd(c->path);
		if (c->path)
			free(c->path);
		return (2);
	}
	if (ft_strcmp("cd", (*cmd->cmd)->content) == 0 && is_in_env("HOME") == 1)
	{
		c->path = get_venv("HOME");
		if (c->path == NULL)
			return (err_msg(4, "IGNORE", 1));
	}
	else if ((*cmd->cmd)->next && ft_strcmp((".."), (*cmd->cmd)->next->content) == 0)
		c->path = get_previous_dir(getcwd(c->cwd, sizeof(c->cwd)));
	else if (ft_strcmp("cd", (*cmd->cmd)->content) == 0 && is_in_env("HOME") == 0)
	{
		*cmd->cmd = c->tmp;
		return (err_msg(4, "IGNORE", 1));
	}
	return(0);
}

int	invalid_option(t_cmd *cmd, t_cd *c)
{
	if (ft_strlen((*cmd->cmd)->next->content) == 1)
		c->path = get_venv("OLDPWD");
	else
	{
		c->msg_err = ft_strjoin("cd: ", (*cmd->cmd)->next->content);
		c->msg_err = ft_strjoin_mod(c->msg_err, ": invalid option\ncd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n", 1);
		err_write(c->msg_err, 2);
		free(c->msg_err);
		return (1);
	}
	return(0);
}

int	cd_lst_two_tok(t_cmd *cmd, t_cd *c)
{
	if (handl_root(cmd, c) == 0)
		return (0);
	else if (ft_lstsize(*cmd->cmd) == 2 && (*cmd->cmd)->next->content[0] == '-')
	{
		if (invalid_option(cmd, c) == 1)
			return (1);
	}
	else if (ft_lstsize(*cmd->cmd) == 2 && (*cmd->cmd)->next->content[0] == '~')
	{
		if (is_in_env("HOME") == 0)
			return (err_msg(4, "IGNORE", 2));
		c->path = get_venv("HOME");
	}
	else
		cd_directory(c, cmd);
	return (0);
}

int	end_cd(t_cmd *cmd, t_cd *c)
{
	if (err_cd(cmd, c->path) == 1)
		return (1);
	*cmd->cmd = c->tmp;
	modify_pwd(c->path);
	free(c->path);
	set_old_path(c->old_path);
	free(c);
	return (0);
}

int	ft_cd(t_cmd *cmd)
{
	t_cd	*c;
	int		ret;

	c = malloc(sizeof(t_cd));
	ft_memset(c, 0, sizeof(ft_cd));
	c->tmp = *cmd->cmd;
	c->path = NULL;
	if (cmd->data->x->nb_cmd > 1)
    {
		if (err_nb_cmd(cmd, c->path) == 1)
			return (1);
    }
	c->old_path = getcwd(c->cwd, sizeof(c->cwd));
	ret = cd_home(cmd, c);
	if (ret != 0)
		return (ret);
	if (ft_lstsize(*cmd->cmd) <= 2)
	{
		if (handl_root(cmd, c) == 0)
			return (0);
		else if (ft_lstsize(*cmd->cmd) == 2 && (*cmd->cmd)->next->content[0] == '-')
		{
			if (invalid_option(cmd, c) == 1)
				return (1);
		}
		else if (ft_lstsize(*cmd->cmd) == 2 && (*cmd->cmd)->next->content[0] == '~')
		{
			if (is_in_env("HOME") == 0)
				return (err_msg(4, "IGNORE", 2));
			c->path = get_venv("HOME");
		}
		else
			cd_directory(c, cmd);
	printf("ok\n");
	}
	else
	{
		*cmd->cmd = c->tmp;
		return (err_msg(3, "IGNORE", 1));
	}
	end_cd(cmd, c);
	return (0);

}