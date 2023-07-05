/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:26:50 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/05 16:30:07 by jthuysba         ###   ########.fr       */
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

void	free_hdoc_tools(t_hdoc *hdoc, char *input)
{
	if (hdoc->delim)
		free(hdoc->delim);
	if (input)
		free(input);
	close(hdoc->hd_pipe[0]);
	close(hdoc->hd_pipe[1]);
}

/* Ecrit str dans fd (avec un \n) */
void	write_in_fd(char *str, int fd)
{
	if (!str)
		return ;
	(void)write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

char	*substitute_hdoc(char *input, t_minishell *data)
{
	char			*result;
	t_substitution	*s;

	s = malloc(sizeof(t_substitution));
	ft_memset(s, 0, sizeof(t_substitution));
	if (!input)
		return (NULL);
	while ((s->i <= ft_strlen(input)) && input[s->i])
	{
		sub_dollar_hdoc(s, input, data);
	}
	result = ft_strdup(s->new_content);
	free(s->new_content);
	free(input);
	free(s);
	return (result);
}
