/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:54:54 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/25 14:51:28 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Setup les pipes
int	setup_pipes(t_exec *data)
{
	int	i;

	data->nb_cmd = nb_cmd(*data->token);
	data->nb_pipes = data->nb_cmd - 1;
	i = 0;
	if (data->nb_pipes == 0)
		return (0);
	data->fd = malloc(sizeof(int *) * data->nb_pipes);
	if (!data->fd)
		return (1);
	while (i < data->nb_pipes)
	{
		data->fd[i] = malloc(sizeof(int) * 2);
		if (!data->fd[i])
			return (1);
		if (pipe(data->fd[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}
