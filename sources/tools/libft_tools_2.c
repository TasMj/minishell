/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:45:54 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/05 21:06:20 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	char	*ss1;
	char	*ss2;
	size_t	i;

	ss1 = s1;
	ss2 = s2;
	i = 0;
	while (i < n)
	{
		if (ss1[i] == ss2[i])
			i++;
		else
			return ((unsigned char)ss1[i] - (unsigned char)ss2[i]);
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == 0)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

long long	ft_atoi(const char *nptr)
{
	long long	res;
	int			i;
	int			sgn;

	i = 0;
	res = 0;
	sgn = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sgn = -sgn;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if ((res > 2147483647 && sgn == 1) || (res < -2147483648 && sgn == -1))
			return (-1);
		res = (res * 10) + (nptr[i] - 48);
		i++;
	}
	return (res * sgn);
}
