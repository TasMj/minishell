/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:58:55 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/16 14:35:50 by jthuysba         ###   ########.fr       */
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
	int j = 0;
	i = 0;

	while (i <= end)
	{
		j = 0;
		while (j < 2)
		{
			// printf("fd = %d\n", data->fd[i][j]);
			j++;
		}
		i++;
	}
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
	close_all(data, data->nb_pipes - 1);
	free_fd(data);
}
