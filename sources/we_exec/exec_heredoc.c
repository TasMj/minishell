/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:10:27 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/30 22:06:23 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

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
int	get_delims(t_minishell *data)
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
			if (pipe(data->x->hdoc[i].hd_pipe) < 0)
				return (1);
			i++;
		}
		elem = elem->next;
	}
	return (0);
}

/* Ecrit str dans fd (avec un \n) */
void write_in_fd(char *str, int fd)
{
	if (!str)
		return ;
	(void)write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

/* Ouvre l'ecriture du heredoc */
int	write_in_hdoc(t_hdoc *hdoc)
{
	char	*input;
	
	while (1)
	{
		input = readline("> ");
		/* Si l'input est le delimiteur on arrete d'ecrire dans le hdoc */
		if (!input || ft_strncmp(input, hdoc->delim, ft_strlen(input)) == 0)
			break ;
		/* Sinon on ecrit le input dans la pipe d'ecriture du heredoc */
		write_in_fd(input, hdoc->hd_pipe[1]);
		free(input);
	}
	close(hdoc->hd_pipe[0]);
	close(hdoc->hd_pipe[1]);
	return (0);
}

/* Child process dans lequel on va remplir le heredoc */
int	heredoc_child(t_xek *x)
{
	int	i;
	
	i = 0;
	while (i < x->nb_hdoc)
	{
		/* Tant qu'on a des hdoc on les ouvrent et on ecrit dedans un par un */
		write_in_hdoc(&(x->hdoc[i]));
		i++;
	}
	exit(0);
}

int	exec_heredoc(t_minishell *data)
{
	pid_t	pid;
	
	data->x->nb_hdoc = nb_hdoc(data);
	if (data->x->nb_hdoc == 0)
		return (0);
	/* On alloue un t_hdoc pour chaque hdoc */
	data->x->hdoc = malloc(sizeof(t_heredoc) * data->x->nb_hdoc);
	if (!data->x->hdoc)
		return (1);
	get_delims(data);
	
	/* On cree un process dans lequel on va ouvrir tous les hdoc un par un */
	pid = fork();
	if (pid == 0)
		heredoc_child(data->x);
	waitpid(pid, NULL, 0);
	return (0);
}