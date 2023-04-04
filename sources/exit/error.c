/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:28:23 by tas               #+#    #+#             */
/*   Updated: 2023/04/03 12:43:20 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_msg(int n)
{	
	if (n == 0)
		write(2, ERR_REDIR_IN_OUT, ft_strlen(ERR_REDIR_IN_OUT));
	else if (n == 1)
		write(2, ERR_QUOTE, ft_strlen(ERR_QUOTE)); // faire une fonction solo pour ça
	else if (n == 2)
		write(2, ERR_CMD, ft_strlen(ERR_CMD));
	return (1);
}