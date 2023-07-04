/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:10:27 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/04 13:53:38 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Retourne le nombre de hdoc dans les tokens */
int	nb_hdoc(t_minishell *data)
{
	t_list	*elem;
	int		count;

	elem = *(data->token);
	count = 0;
	while (elem)
	{
		if (elem->type == HEREDOC)
			count++;
		elem = elem->next;
	}
	return (count);
}

/* Recupere tous les delimiteurs des heredoc */
static int	get_delims(t_minishell *data)
{
	t_list	*elem;
	int		i;

	elem = *(data->token);
	i = 0;
	while (elem)
	{
		/* Quand on trouve un heredoc on recup le delim
		et on ouvre la pipe dans laquelle on va ecrire */
		if (elem->type == HEREDOC)
		{
			data->x->hdoc[i].delim = ft_strdup(elem->next->content);
			if (elem->next->quote_trace == 1)
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

/* Ecrit str dans fd (avec un \n) */
static void write_in_fd(char *str, int fd)
{
	if (!str)
		return ;
	(void)write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

char *substitute_hdoc(char *input, t_minishell *data)
{
	char			*result;
	t_substitution	*s;
	
	s = malloc(sizeof(t_substitution));
	ft_memset(s, 0, sizeof(t_substitution));
	while (input[s->i])
	{
		sub_dollar_hdoc(s, input, data);
	}
	result = ft_strdup(s->new_content);
	free(input);
	free(s);
	return (result);
}

/* Ouvre l'ecriture du heredoc */
static int	write_in_hdoc(t_hdoc *hdoc, t_minishell *data)
{
	char	*input;
	(void) data;

	// signal(SIGINT, &signal_heredoc);
	while (1)
	{
		input = readline("> ");
		// for(int i = 0; input[i]; i++)
		// 	write(1, &input[i], 1);
		// write(1, "\n", 1);
		/* Si l'input est le delimiteur on arrete d'ecrire dans le hdoc */
		if (!input || ft_strcmp(input, hdoc->delim) == 0)
		{
			free(hdoc->delim);
			free(input);
			break ;
		}

		if (hdoc->flag_sub == 0)
			input = substitute_hdoc(input, data);
		
		/* Sinon on ecrit le input dans la pipe d'ecriture du heredoc */
		write_in_fd(input, hdoc->hd_pipe[1]);
		free(input);
	}
	close(hdoc->hd_pipe[0]);
	close(hdoc->hd_pipe[1]);
	return (0);
}

/* Child process dans lequel on va remplir le heredoc */
static int	heredoc_child(t_minishell *data)
{
	int	i;
	
	i = 0;
	while (i < data->x->nb_hdoc)
	{
		/* Tant qu'on a des hdoc on les ouvrent et on ecrit dedans un par un */
		write_in_hdoc(&(data->x->hdoc[i]), data);
		i++;
	}

	// METTRE ft_exit()
	// exit(0);
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
	/* On alloue un t_hdoc pour chaque hdoc */
	data->x->hdoc = malloc(sizeof(t_hdoc) * data->x->nb_hdoc);
	if (!data->x->hdoc)
		return (1);
	get_delims(data);
	
	/* On cree un process dans lequel on va ouvrir tous les hdoc un par un */
	pid = fork();
	if (pid == 0)
		heredoc_child(data);
	waitpid(pid, NULL, 0);
	
	i = 0;
	while (i < data->x->nb_hdoc)
	{
		free(data->x->hdoc[i].delim);
		close(data->x->hdoc[i].hd_pipe[1]);
		i++;
	}
	return (0);
}