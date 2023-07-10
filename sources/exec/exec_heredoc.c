/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:10:27 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/10 16:43:22 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Recupere tous les delimiteurs des heredoc */
static int	get_delims(t_minishell *data)
{
	t_list	*elem;
	int		i;

	elem = *(data->token);
	i = 0;
	while (elem)
	{
		if (elem->type == HEREDOC)
		{
			data->x->hdoc[i].delim = ft_strdup(elem->next->content);
			if (elem->next->quote_trace == 1
				|| check_dollar(data->x->hdoc[i].delim) == 1)
				data->x->hdoc[i].flag_sub = 1;
			else
				data->x->hdoc[i].flag_sub = 0;
			if (pipe(data->x->hdoc[i].hd_pipe) < 0)
				return (1);
			i++;
		}
		elem = elem->next;
	}
	return (0);
}

static char	*read_n_write(t_hdoc *hdoc, t_minishell *data)
{
	char	*input;

	input = readline("> ");
	if (!input || ft_strcmp(input, hdoc->delim) == 0)
		return (NULL);
	if (input[0] == 0)
		write_in_fd("", hdoc->hd_pipe[1]);
	else
	{
		if (hdoc->flag_sub == 0)
			input = substitute_hdoc(input, data);
		write_in_fd(input, hdoc->hd_pipe[1]);
	}
	return (input);
}

/* Ouvre l'ecriture du heredoc */
static int	write_in_hdoc(t_hdoc *hdoc, t_minishell *data)
{
	char	*input;

	handle_signal_hdoc();
	input = read_n_write(hdoc, data);
	while (input && (!input[0] || ft_strcmp(input, hdoc->delim))
		&& (g_exit_code != 130))
	{
		free(input);
		if (g_exit_code == 130)
			break ;
		input = read_n_write(hdoc, data);
	}
	return (free_hdoc_tools(hdoc, input), 0);
}

/* Child process dans lequel on va remplir le heredoc */
static int	heredoc_child(t_minishell *data)
{
	int	i;

	i = 0;
	while (i < data->x->nb_hdoc)
	{
		write_in_hdoc(&(data->x->hdoc[i]), data);
		i++;
	}
	ft_exit(data);
	return (0);
}

int	exec_heredoc(t_minishell *data)
{
	pid_t	pid;
	int		i;

	data->x->nb_hdoc = nb_hdoc(data);
	if (data->x->nb_hdoc == 0)
		return (0);
	data->x->hdoc_index = 0;
	data->x->hdoc = malloc(sizeof(t_hdoc) * data->x->nb_hdoc);
	if (!data->x->hdoc)
		return (1);
	get_delims(data);
	signal_ignore();
	pid = fork();
	if (pid == 0)
		heredoc_child(data);
	waitpid(pid, NULL, 0);
	set_signal();
	i = 0;
	while (i < data->x->nb_hdoc)
	{
		free(data->x->hdoc[i].delim);
		close(data->x->hdoc[i].hd_pipe[1]);
		i++;
	}
	return (0);
}
