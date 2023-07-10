/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:10:01 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/10 22:27:26 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	invalid_option(t_cmd *cmd, t_cd *c, t_minishell *data)
{
	if (ft_strlen((*cmd->cmd)->next->content) == 1)
		c->path = get_venv("OLDPWD", data);
	else
	{
		c->msg_err = ft_strjoin("cd: ", (*cmd->cmd)->next->content);
		c->msg_err = ft_strjoin_mod(c->msg_err, ": \
		invalid option\ncd: usage: cd [-L|[-P [-e]] [-@]] [dir]\n", 1);
		err_write(c->msg_err, 2);
		free(c->msg_err);
		free(c);
		return (1);
	}
	return (0);
}

int	end_cd(t_cmd *cmd, t_cd *c, t_minishell *data)
{
	if (err_cd(cmd, c->path) == 1)
	{
		free(c);
		return (1);
	}
	*cmd->cmd = c->tmp;
	modify_pwd(c->path, data);
	set_old_path(c->old_path, data);
	if (c->path)
		free(c->path);
	free(c);
	return (0);
}

int	intit_cd(t_cmd *cmd, t_cd *c)
{
	ft_memset(c, 0, sizeof(ft_cd));
	c->tmp = *cmd->cmd;
	c->path = NULL;
	if (cmd->data->x->nb_cmd > 1)
	{
		printf("%s\n", c->path);
		if (err_nb_cmd(cmd, c->path) == 1)
		{
			free(c);
			return (1);
		}
	}
	c->old_path = getcwd(c->cwd, sizeof(c->cwd));
	return (0);
}

int	home_unset(t_cd *c, t_minishell *data)
{
	if (is_in_env("HOME", data) == 0)
	{
		free(c);
		return (err_msg(4, "IGNORE", 2));
	}
	c->path = get_venv("HOME", data);
	return (0);
}

int	cd_one_tok(t_cmd *cmd, t_cd *c, t_minishell *data)
{
	if (handl_root(cmd, c, data) == 1)
		return (1);
	else if (ft_lstsize(*cmd->cmd) == 2 && (*cmd->cmd)->next->content[0] == '-')
	{
		if (invalid_option(cmd, c, data) == 1)
			return (1);
	}
	else if (ft_lstsize(*cmd->cmd) == 2 && (*cmd->cmd)->next->content[0] == '~')
	{
		if (home_unset(c, data) == 1)
			return (1);
	}
	else
	{
		if (cd_directory(c, cmd, data) == 1)
			return (1);
	}
	return (0);
}
