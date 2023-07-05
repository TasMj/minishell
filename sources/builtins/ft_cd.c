/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:10:00 by tas               #+#    #+#             */
/*   Updated: 2023/07/05 21:31:49 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* keep the last pwd */
int	set_old_path(char *path)
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

/* return the previous directory */
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

int	modify_pwd(char *new_pwd)
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

int	ft_cd(t_cmd *cmd)
{
	t_cd	*c;
	int		ret;

	c = malloc(sizeof(t_cd));
	if (intit_cd(cmd, c) == 1)
		return (1);
	ret = cd_home(cmd, c);
	if (ret != 0)
		return (ret);
	if (ft_lstsize(*cmd->cmd) <= 2)
	{
		if (cd_one_tok(cmd, c) == 1)
			return (1);
	}
	else
	{
		*cmd->cmd = c->tmp;
		return (err_msg(3, "IGNORE", 1));
	}
	end_cd(cmd, c);
	return (0);
}
