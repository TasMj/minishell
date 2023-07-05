/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:43:39 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/05 06:43:53 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>

void	handle_signal(int sigid)
{
	t_minishell *data;

	data = singleton_minishell();
	if (sigid == SIGINT)
	{
		// printf("here2\n");
		data->code_err = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	if (sigid == SIGQUIT)
	{
		return ;
	}
}

void	ctrl_c_hdoc(int sig)
{
	(void) sig;
	close(0);
	printf("\n");
	singleton_minishell()->code_err = -42;
}

void	handle_signal_hdoc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c_hdoc);
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

void	set_signal(void)
{
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ctr_bs(int sigid)
{
	if (sigid == SIGQUIT)
	{
		printf("here1\n");
		return ;
	}
}	
