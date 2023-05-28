// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   setup_pipes.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/05/15 15:54:54 by jthuysba          #+#    #+#             */
// /*   Updated: 2023/05/23 21:29:19 by jthuysba         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// // Compte les pipes dans les token
// int	count_pipes(t_list *token)
// {
// 	int	count;

// 	count = 0;
// 	while (token)
// 	{
// 		if (token->type == PIPE)
// 			count++;
// 		token = token->next;
// 	}
// 	return (count);
// }

// // Setup les pipes
// void	setup_pipes(t_exec *data)
// {
// 	int	i;

// 	data->nb_cmd = nb_cmd(*data->token);
// 	data->nb_pipes = count_pipes(*(data->token));
// 	i = 0;
// 	if (data->nb_pipes == 0)
// 		return ;
// 	data->fd = malloc(sizeof(int *) * data->nb_pipes);
// 	while (i < data->nb_pipes)
// 	{
// 		data->fd[i] = malloc(sizeof(int) * 2);
// 		if (pipe(data->fd[i]) < 0)
// 		{
// 			close_all(data, i);
// 			return ;
// 		}
// 		i++;
// 	}
// }
