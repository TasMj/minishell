/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:45:54 by tmejri            #+#    #+#             */
/*   Updated: 2023/02/22 17:01:05 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char **all_split(char *s, char c, char d)
{
	if (c == ' ')
		return (ft_split(s, ' '));
	if (d == 34)
		return (ft_split_bracket(s, 34));

	return (NULL);
}