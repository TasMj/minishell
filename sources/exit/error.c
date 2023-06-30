/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:28:23 by tas               #+#    #+#             */
/*   Updated: 2023/06/30 14:53:14 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_msg(int n)
{
	if (n == 0)
		err_write(ERR_REDIR_IN_OUT);
	else if (n == 1)
		err_write(ERR_QUOTE);
	else if (n == 127)
		err_write(ERR_CMD);
	else if (n == 3)
		err_write(ERR_MANY_ARG);
	else if (n == 4)
		err_write(ERR_HOME);
	else if (n == 5)
		err_write(ERR_EXPORT);
	return (1);
}
