/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_tools_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:02:53 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/05 21:03:39 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* return 1 if space or new line */
int	is_a_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

/* return 1 if space, <, <<, >, >>, | or new line */
int	is_a_separator(char c)
{
	if (is_a_space(c) == 1 || c == '|' || c == '>' || c == '<' || c == '\0')
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

static int	ft_alnu_m(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (1);
	else
		return (0);
}

int	is_alphanum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_alnu_m(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
