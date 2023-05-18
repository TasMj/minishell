/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:20:11 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/18 15:40:26 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

int	set_stdin(t_cmd *cmd)
{
	int		i;
	char	*file;
	int		fd;

	i = 0;
	while (cmd->cmd[i][0] != '<')
		i++;
	if (cmd->cmd[i + 1])
		i++;
	else
		return (1);
	file = ft_strdup_size(cmd->cmd[i], ft_strlen(cmd->cmd[i]));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	cmd->fd_in = fd;
	free(file);
	return (0);
}

void	set_op_fd(t_cmd *cmd)
{
	if (cmd->type == STDIN)
	{
		set_stdin(cmd);
	}
}

// Setup fd in et out pour chaque commande
void	set_fd(t_cmd *cmd, t_exec *data)
{
	if (data->nb_pipes == 0)
	{
		cmd->fd_in = STDIN_FILENO;
		cmd->fd_out = STDOUT_FILENO;	
	}
	else if (cmd->id == 0)
	{
		cmd->fd_in = STDIN_FILENO;
		cmd->fd_out = data->fd[0][1];	
	}
	else if (cmd->id == data->nb_pipes)
	{
		cmd->fd_in = data->fd[cmd->id - 1][0];
		cmd->fd_out = STDOUT_FILENO;
	}
	else
	{
		cmd->fd_in = data->fd[cmd->id - 1][0];
		cmd->fd_out = data->fd[cmd->id][1];
	}
	set_op_fd(cmd);
}