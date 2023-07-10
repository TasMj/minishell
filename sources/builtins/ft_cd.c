/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:10:00 by tas               #+#    #+#             */
/*   Updated: 2023/07/10 22:28:38 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* keep the last pwd */
int	set_old_path(char *path, t_minishell *data)
{
	t_list	*tmp;
	char	*copy_env;

	if (is_in_env("OLDPWD", data) == 0 || !path)
		return (1);
	tmp = *data->env;
	while (*data->env)
	{
		copy_env = del_equal((*data->env)->content);
		if (ft_strcmp(copy_env, "OLDPWD") == 1)
			(*data->env) = (*data->env)->next;
		else if (ft_strcmp(copy_env, "OLDPWD") == 0)
		{
			free((*data->env)->content);
			(*data->env)->content = ft_strjoin("OLDPWD=", path);
			*data->env = tmp;
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

int	modify_pwd(char *new_pwd, t_minishell *data)
{
	char	*copy_env;
	t_list	*tmp;

	tmp = *data->env;
	while (*data->env)
	{
		copy_env = del_equal((*data->env)->content);
		if (ft_strcmp(copy_env, "PWD") == 1)
			(*data->env) = (*data->env)->next;
		else if (ft_strcmp(copy_env, "PWD") == 0)
		{
			free((*data->env)->content);
			(*data->env)->content = ft_strjoin("PWD=", new_pwd);
			*data->env = tmp;
			free(copy_env);
			return (1);
		}
		free(copy_env);
	}
	*data->env = tmp;
	return (0);
}

int	ft_cd(t_cmd *cmd, t_minishell *data)
{
	t_cd	*c;
	int		ret;

	c = malloc(sizeof(t_cd));
	intit_cd(cmd, c);
	if (singleton_minishell()->x->nb_cmd > 1)
		return (0);
	ret = cd_home(cmd, c, data);
	if (ret != 0)
		return (ret);
	if (ft_lstsize(*cmd->cmd) <= 2)
	{
		if (cd_one_tok(cmd, c, data) == 1)
			return (1);
	}
	else
	{
		*cmd->cmd = c->tmp;
		free(c);
		return (err_msg(3, "IGNORE", 1));
	}
	end_cd(cmd, c, data);
	return (0);
}
