/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:45:54 by tmejri            #+#    #+#             */
/*   Updated: 2023/03/03 10:37:30 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char		*ss;
	size_t		i;

	i = 0;
	ss = (char *)s;
	while (i < n)
	{
		ss[i] = (char)c;
		i++;
	}
	s = (void *)ss;
	return (s);
}

char	*ft_strdup_size(char *s, int size)
{
	char	*ss;
	int		i;

	i = 0;
	ss = (char *)malloc(sizeof(char) * size + 1);
	if (ss == 0)
		return (NULL);
	while (i < size)
	{
		ss[i] = s[i];
		i++;
	}
	ss[i] = '\0';
	return (ss);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
