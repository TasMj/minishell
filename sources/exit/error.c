/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:28:23 by tas               #+#    #+#             */
/*   Updated: 2023/05/25 14:45:24 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_msg(int n)
{	
	write(2, "minishell: ", 11);
	if (n == 0)
		write(2, ERR_REDIR_IN_OUT, ft_strlen(ERR_REDIR_IN_OUT));
	else if (n == 1)
		write(2, ERR_QUOTE, ft_strlen(ERR_QUOTE));
	else if (n == 2)
		write(2, ERR_CMD, ft_strlen(ERR_CMD));
	else if (n == 3)
		write(2, ERR_MANY_ARG, ft_strlen(ERR_MANY_ARG));
	return (1);
}
