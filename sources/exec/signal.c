/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:43:39 by tmejri            #+#    #+#             */
/*   Updated: 2023/06/29 15:37:28 by jthuysba         ###   ########.fr       */
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