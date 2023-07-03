/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:24:17 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/03 11:46:16 by jthuysba         ###   ########.fr       */
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

static void	put_nbr(char *str, long int n, size_t i)
{
	if (i > 0)
		put_nbr(str, n / 10, --i);
	str[i] = (n % 10) + '0';
}

char	*ft_itoa(int n)
{
	size_t		len;
	long int	nb;
	char		*str;
	int			neg;

	nb = n;
	len = 0;
	neg = 0;
	if (nb < 0)
		len++;
	len += nbr_len(nb);
	str = malloc(sizeof(char) * (len + 1));
	ft_memset(str, 0, len + 1);
	if (nb < 0)
	{
		neg = 1;
		nb = nb * (-1);
	}
	put_nbr(str, nb, len);
	if (neg)
		str[0] = '-';
	return (str);
}

int	put_str_err(char *error)
{
	int	i;

	i = 0;
	while (error[i])
	{
		write(2, &error[i], 1);
		i++;
	}
	return (0);
}

int	err_write(char *error, int code_err)
{
	int	i;

	i = 0;
	write(code_err, "minishell: ", 11);
	
	while (error[i])
	{
		write(code_err, &error[i], 1);
		i++;
	}
	return (0);
}
