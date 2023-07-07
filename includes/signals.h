/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:05:55 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/06 02:34:10 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

/******************************************************************************/
/*                                includes                                    */
/******************************************************************************/
# include "minishell.h"

/******************************************************************************/
/*                                fonctions                                   */
/******************************************************************************/

t_minishell	*singleton_minishell(void);
void		ctrl_c_hdoc(int sig);
void		handle_term_sig(int ret);
void		signal_default(void);
void		handle_signal_hdoc(void);
void		handle_signal(int sigid);
void		signal_ignore(void);
void		set_signal(void);
void		signal_signal(int signal);

#endif