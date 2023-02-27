/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:28:23 by tas               #+#    #+#             */
/*   Updated: 2023/02/27 11:38:18 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_msg(int n)
{	
    printf("minishell: ");
	if (n == 0)
		write(1, ERR_REDIR_IN_OUT, ft_strlen(ERR_REDIR_IN_OUT));
	else if (n == 1)
		write(1, ERR_QUOTE, ft_strlen(ERR_QUOTE)); // faire une fonction solo pour ça

	return (1);
}