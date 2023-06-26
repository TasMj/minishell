/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:43:39 by tmejri            #+#    #+#             */
/*   Updated: 2023/06/26 17:32:15 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sigid)
{
	if (sigid == SIGINT)
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		write(2, "\n", 1);
		rl_redisplay();
	}
	if (sigid == SIGQUIT)
	{
		return ;
	}
}

// void	handle_signal_heredoc(int sigid)
// {
		// if (sigid == SIGINT)
	// {
		// rl_replace_line("", 1);
		// rl_on_new_line();
		// write(2, "\n", 1);
		// rl_redisplay();
	// }
	// if (sigid == SIGQUIT)
	// {
		// return ;
	// }
// 
// }

// void	handle_signal_prog(int sigid)
// {
	
// }


void	ctr_bs(int sigid)
{
	if (sigid == SIGQUIT)
		return ;
}
