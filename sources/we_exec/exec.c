/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:57:13 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/30 01:18:40 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_process(t_xek *x)
{
	int	i;

	i = 0;
	while (i < x->nb_cmd)
	{
		x->cmd[i].pid = fork();
		if (x->cmd[i].pid < 0)
			return (1);
		if (x->cmd[i].pid == 0)
		{
			printf("Hello from process %d\n", i);
			return (0);
		}
		i++;
	}
	return (0);
}

/* Execute les commandes */
int	go_exec(t_xek *x)
{
	int	i;

	if (pipe(x->pipe) < 0)
		return (1);
	
	launch_process(x);


	i = 0;
	while (i < x->nb_cmd)
	{
		waitpid(x->cmd[i].pid, NULL, 0);
		i++;
	}
	return (0);
}

/* Execute les tokens
-> cat < file | wc -l > file2 */
int	we_exec(t_minishell *data)
{
	data->x = malloc(sizeof(t_xek));

	prep_cmd(data);

	go_exec(data->x);

	destroy_all(data->x);
	return (0);
}