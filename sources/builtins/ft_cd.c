/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:10:00 by tas               #+#    #+#             */
/*   Updated: 2023/05/26 13:24:00 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

/* check if directory and not file */
int	is_dir(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (1);
	return (S_ISDIR(st.st_mode));
}

char	*get_previous_dir(char *str)
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

int	err_cd(t_list **list, char *path)
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

char	*set_path(char *path, t_list **list)
{
	char	cwd[1024];
	int		size;

	size = ft_strlen(getcwd(cwd, sizeof(cwd)));
	path = ft_strdup_size((getcwd(cwd, sizeof(cwd))), size);
	path = ft_strjoin(path, "/");
	path = ft_strjoin(path, (*list)->next->content);
	return (path);
}

int	ft_cd(t_list **list)
{
	char	cwd[1024];
	char	*path;
	t_list	*tmp;

	tmp = *list;
	path = NULL;
	if (ft_strcmp("cd", (*list)->content) == 0 && (*list)->next == NULL && is_in_env("HOME") == 1)
		path = ft_strdup_size(return_var_env("HOME"), ft_strlen(return_var_env("HOME")));
	else if (ft_strcmp("cd", (*list)->content) == 0 && (*list)->next == NULL && is_in_env("HOME") == 0)
	{
		*list = tmp;
		return (err_msg(4));
	}
	else if ((*list)->next && ft_strcmp((".."), (*list)->next->content) == 0)
	{
		if (ft_lstsize(*list) >= 3)
			return (err_msg(3));
		path = get_previous_dir(getcwd(cwd, sizeof(cwd)));
	}
	else
	{
		if (ft_lstsize(*list) > 2)
			return (err_msg(3));
		path = set_path(path, list);
	}
	if (err_cd(list, path) == 1)
		return (1);
	free(path);
	*list = tmp;
	return (0);
}
