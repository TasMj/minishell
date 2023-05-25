/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:58:55 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/25 17:03:33 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Free toutes les pipes
void	free_fd(t_exec *data)
{
	int	i;

	i = 0;
	while (i < data->nb_pipes)
	{
		free(data->fd[i]);
		i++;
	}
	free(data->fd);
}

// Ferme toutes les pipes jusqu'a la pipe end
void	close_all(t_exec *data, int end)
{
	int	i;
	
	i = 0;
	while (i <= end)
	{
		close(data->fd[i][0]);
		close(data->fd[i][1]);
		i++;
	}
}

//Free toutes les struct de l'exec et close les pipes
void	clean_all(t_exec *data)
{
	int	i;
	
	i = 0;
	while (i < data->nb_cmd)
	{
		if (data->cmd[i].fd_in != STDIN_FILENO)
			close(data->cmd[i].fd_in);
		if (data->cmd[i].fd_out != STDOUT_FILENO)
			close(data->cmd[i].fd_out);
		if (data->cmd[i].cmd)
			free_list(data->cmd[i].cmd);
		i++;
	}
	if (data->nb_pipes > 0)
	{
		close_all(data, data->nb_pipes - 1);
		free_fd(data);
	}
}
