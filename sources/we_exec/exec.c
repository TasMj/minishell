/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:57:13 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/28 16:55:06 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Execute les tokens
-> cat < file | wc -l > file2 */
int	we_exec(t_minishell *data)
{
	data->x = malloc(sizeof(t_xek));
	prep_cmd(data);
	return (0);
}