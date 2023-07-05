/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:43:39 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/05 04:30:05 by jthuysba         ###   ########.fr       */
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

void	set_signal(void)
{
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_ignore(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ctr_bs(int sigid)
{
	if (sigid == SIGQUIT)
		return ;
}	

void	signal_heredoc(int sig, t_minishell *data)
{
	(void)sig;
	close(STDIN_FILENO);
	data->code_err = 128;
	return ;
}