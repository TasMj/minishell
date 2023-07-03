/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:10:00 by tas               #+#    #+#             */
/*   Updated: 2023/07/03 13:19:07 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_list **list);


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
			// free((*g_list_env)->content);
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

/* return if not a file or a directory */
static int	err_cd(t_cmd *cmd, char *path)
{
	char	*msg_err;
	(void) cmd;

	if (is_dir(path) == 0)
	{
		// msg_err = ft_strjoin((*cmd->cmd)->next->content, ": Not a directory\n");
		// err_write(msg_err, 2);
		put_str_err("minishell: cd: ");
		put_str_err((*cmd->cmd)->next->content);
		put_str_err(": Not a directory\n");
		cmd->data->code_err = 127;
		// free(msg_err);
		free(path);
		return (1);

		// printf("minishell: cd: %s: Not a directory\n", (*cmd->cmd)->next->content);
		err_write("cd: Not a directory\n", 1);
		free(path);
		return (1);
	}
	if (chdir(path) == -1)
	{
			msg_err = ft_strjoin((*cmd->cmd)->next->content, ": No such file or directory\n");
			err_write(msg_err, 2);
			cmd->data->code_err = 127;
			free(msg_err);
			free(path);
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

int	ft_cd(t_cmd *cmd)
{
	char	cwd[1024];
	char	*path;
	t_list	*tmp;
	char	*msg_err;

	(void)msg_err;
	tmp = *cmd->cmd;
	path = NULL;
	if (cmd->data->x->nb_cmd > 1)
	{
		path = ft_strdup((*cmd->cmd)->next->content);
		if (is_dir(path) == 0)
		{
			put_str_err("minishell: cd: ");
			put_str_err((*cmd->cmd)->next->content);
			put_str_err(": Not a directory\n");
			cmd->data->code_err = 127;
		}
		return (free(path), 0);
	}
	char *old_path = getcwd(cwd, sizeof(cwd));
	// set_old_path(old_path);
	if (ft_strcmp("cd", (*cmd->cmd)->content) == 0 && (*cmd->cmd)->next == NULL && is_in_env("HOME") == 1)
	{
		path = get_venv("HOME");
		if (ft_strlen(path) == 0)
			return (1);
	}
	else if (ft_strcmp("cd", (*cmd->cmd)->content) == 0 && (*cmd->cmd)->next == NULL && is_in_env("HOME") == 0)
	{
		*cmd->cmd = tmp;
		return (err_msg(4, "IGNORE", 1));
	}
	else if ((*cmd->cmd)->next && ft_strcmp((".."), (*cmd->cmd)->next->content) == 0)
		path = get_previous_dir(getcwd(cwd, sizeof(cwd)));
	else if (ft_lstsize(*cmd->cmd) <= 2)
	{
		if (ft_lstsize(*cmd->cmd) == 2 && contain_slash((*cmd->cmd)->next->content) == 0)
			path = get_venv("HOME"); //mettre le bon emplacement
		else if (ft_lstsize(*cmd->cmd) == 2 && (*cmd->cmd)->next->content[0] == '-')
		{
			if (ft_strlen((*cmd->cmd)->next->content) == 1)
				path = get_venv("OLDPWD");
			else
			{
				msg_err = ft_strjoin("cd: ", (*cmd->cmd)->next->content);
				msg_err = ft_strjoin_mod(msg_err, ": invalid option\ncd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n", 1);
				err_write(msg_err, 2);
				free(msg_err);
				return (1);
			}
		}
		else if (ft_lstsize(*cmd->cmd) == 2 && (*cmd->cmd)->next->content[0] == '~')
		{
			path = get_venv("HOME");
		}
		else
		{
			char *home = get_venv("HOME");
			if (ft_strlen((*cmd->cmd)->next->content) >= ft_strlen(home)
			&& ft_strncmp((*cmd->cmd)->next->content, home, ft_strlen(home)) == 0)
				path = ft_strdup((*cmd->cmd)->next->content);
			else
				path = set_path(path, cmd->cmd);
		}
	}
	else
	{
		*cmd->cmd = tmp;
		return (err_msg(3, "IGNORE", 1));
	}
	if (err_cd(cmd, path) == 1)
		return (1);
	*cmd->cmd = tmp;
	free(path);
	set_old_path(old_path);
	return (0);
}
