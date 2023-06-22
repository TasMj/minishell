/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:43:39 by tmejri            #+#    #+#             */
/*   Updated: 2023/06/22 23:13:57 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

void	ctrl_c(int sigid)
{
	if (sigid == SIGINT)
	{
		// write(2, "\n", 1);
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();

		rl_replace_line("", 1);
		rl_on_new_line();
		write(2, "\n", 1);
		rl_redisplay();
		// exit (0);
	}
}

void	ctr_bs(int sigid)
{
	if (sigid == SIGQUIT)
		return ;
}
