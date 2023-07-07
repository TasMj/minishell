/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:43:39 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/07 13:41:16 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

void	handle_signal(int sigid)
{
	if (sigid == SIGINT)
	{
		write(2, "\n", 1);
		singleton_minishell()->code_err = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sigid == SIGQUIT)
		return ;
}

void	ctrl_c_hdoc(int sig)
{
	(void) sig;
	close(0);
	printf("\n");
	singleton_minishell()->code_err = -42;
}

void	signal_signal(int signal)
{
	if (signal == SIGINT)
	{
		singleton_minishell()->code_err = 130;
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else if (signal - 128 == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 20);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
