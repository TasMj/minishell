/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tools_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:07:59 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/05 21:15:50 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_bzero(void *s, size_t n)
{
	char		*ss;
	size_t		i;

	i = 0;
	ss = (char *)s;
	{
		while (i < n)
		{
			ss[i] = '\0';
			i++;
		}
	}
}

void	*ft_calloc(size_t n, size_t size)
{
	int	*arr;

	if (size && n > (size_t) - 1 / size)
		return (0);
	arr = (void *)malloc(n * size);
	if (!arr)
		return (NULL);
	ft_bzero(arr, n * size);
	return (arr);
}

int	ft_strcmp(char *s1, char *s2)
{
	char	*ss1;
	char	*ss2;
	int		i;

	ss1 = s1;
	ss2 = s2;
	i = 0;
	if (ft_strlen(ss1) != ft_strlen(ss2))
		return (1);
	else
	{
		while (i < ft_strlen(ss1))
		{
			if (ss1[i] == ss2[i])
				i++;
			else
				return (1);
		}
	}
	return (0);
}

size_t	nbr_len(long int n)
{
	size_t		i;
	long int	nb;

	nb = n;
	i = 1;
	if (nb < 0)
		nb *= -1;
	while (nb > 9)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

void	put_nbr(char *str, long int n, size_t i)
{
	if (i > 0)
		put_nbr(str, n / 10, --i);
	str[i] = (n % 10) + '0';
}
