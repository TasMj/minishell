/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:28:23 by tas               #+#    #+#             */
/*   Updated: 2023/03/10 16:09:42 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_msg(int n)
{	
	if (n == 0)
		write(1, ERR_REDIR_IN_OUT, ft_strlen(ERR_REDIR_IN_OUT));
	else if (n == 1)
		write(1, ERR_QUOTE, ft_strlen(ERR_QUOTE)); // faire une fonction solo pour ça
	return (1);
}