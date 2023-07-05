/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:17:01 by tas               #+#    #+#             */
/*   Updated: 2023/07/05 14:43:51 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*check si il y a une redirection < in */
int	check_redir_in(char c)
{
	if (!c)
		return (0);
	if (c == 60)
		return (1);
	return (0);
}

/*check si il y a une redirection > out */
int	check_redir_out(char c)
{
	if (!c)
		return (0);
	if (c == 62)
		return (1);
	return (0);
}

/* check if is a heredoc '<<' */
int	check_heredoc(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '<')
	{
		i++;
		if (str[i] && str[i] == '<')
			return (1);
	}
	return (0);
}

/* check if is a append '>>' */
int	check_append(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '>')
	{
		i++;
		if (str[i] && str[i] == '>')
			return (1);
	}
	return (0);
}

int	is_redir(char *str)
{
	if (ft_strlen(str) == 1)
	{
		if (ft_strncmp(str, "|", 1) == 0 || ft_strncmp(str, "<", 1) == 0
			|| ft_strncmp(str, ">", 1) == 0)
			return (1);
	}
	if (ft_strlen(str) == 2)
	{
		if (ft_strncmp(str, "<<", 1) == 0 || ft_strncmp(str, ">>", 1) == 0)
			return (1);
	}
	return (0);
}
