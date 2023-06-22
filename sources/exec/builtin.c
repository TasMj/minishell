/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:42:19 by tmejri            #+#    #+#             */
/*   Updated: 2023/06/22 20:37:44 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

int	exec_builtin(t_cmd *cmd, t_minishell *data)
{
	t_list	*tmp;

	if (!cmd->cmd || ft_lstsize(*cmd->cmd) == 0)
		return (-1);
	tmp = *cmd->cmd;
	if (ft_strlen((*cmd->cmd)->content) == 2 && ft_strncmp((*cmd->cmd)->content, "cd", 2) == 0)
		ft_cd(cmd->cmd);
	else if (ft_strlen((*cmd->cmd)->content) == 4 && ft_strncmp((*cmd->cmd)->content, "echo", 4) == 0)
		ft_echo(cmd->cmd);
	else if (ft_strlen((*cmd->cmd)->content) == 3 && ft_strncmp((*cmd->cmd)->content, "env", 3) == 0)
		ft_env(cmd->cmd);
	else if (ft_strlen((*cmd->cmd)->content) == 4 && ft_strncmp((*cmd->cmd)->content, "exit", 4) == 0)
	{
		printf("here1\n");
		ft_exit(data);
	}
	else if (ft_strlen((*cmd->cmd)->content) == 6 && ft_strncmp((*cmd->cmd)->content, "export", 6) == 0)
		ft_export(cmd->cmd);
	else if (ft_strlen((*cmd->cmd)->content) == 3 && ft_strncmp((*cmd->cmd)->content, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strlen((*cmd->cmd)->content) == 5 && ft_strncmp((*cmd->cmd)->content, "unset", 5) == 0)
		ft_unset(cmd->cmd);
	else
		return (1);
	*cmd->cmd = tmp;
	return (0);
}
