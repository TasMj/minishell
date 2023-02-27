/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:45:54 by tmejri            #+#    #+#             */
/*   Updated: 2023/02/25 21:00:15 by tas              ###   ########.fr       */
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

char	*ft_strdup(const char *s)
{
	char	*ss;
	int		i;
	int		len_s;

	i = 0;
	len_s = ft_strlen(s);
	ss = (char *)malloc(sizeof(char) * len_s + 1);
	if (ss == 0)
		return (NULL);
	while (s[i])
	{
		ss[i] = s[i];
		i++;
	}
	ss[i] = '\0';
	return (ss);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
