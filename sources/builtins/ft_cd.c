/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:10:00 by tas               #+#    #+#             */
/*   Updated: 2023/06/23 12:29:19 by tas              ###   ########.fr       */
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
static int	is_dir(char *path)
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
static int	err_cd(t_list **list, char *path)
{
	if (is_dir(path) == 0)
	{
		printf("minishell: cd: %s: Not a directory\n", (*list)->next->content);
		free(path);
		return (1);
	}
	if (chdir(path) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", \
		(*list)->next->content);
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

int	ft_cd(t_list **list)
{
	char	cwd[1024];
	char	*path;
	t_list	*tmp;

	tmp = *list;
	path = NULL;
	char *old_path = getcwd(cwd, sizeof(cwd));
	set_old_path(old_path);
	if (ft_strcmp("cd", (*list)->content) == 0 && (*list)->next == NULL && is_in_env("HOME") == 1)
		path = get_venv("HOME");
	else if (ft_strcmp("cd", (*list)->content) == 0 && (*list)->next == NULL && is_in_env("HOME") == 0)
	{
		*list = tmp;
		return (err_msg(4));
	}
	else if ((*list)->next && ft_strcmp((".."), (*list)->next->content) == 0)
		path = get_previous_dir(getcwd(cwd, sizeof(cwd)));
	else if (ft_lstsize(*list) <= 2)
		path = set_path(path, list);
	else
	{
		*list = tmp;
		return (err_msg(3));
	}
	if (err_cd(list, path) == 1)
		return (1);
	free(path);
	*list = tmp;
	return (0);
}
