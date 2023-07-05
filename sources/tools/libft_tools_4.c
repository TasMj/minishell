/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tools_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:07:59 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/05 21:09:50 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	err_write(char *error, int out)
{
	int	i;

	i = 0;
	write(out, "minishell: ", 11);
	while (error[i])
	{
		write(out, &error[i], 1);
		i++;
	}
	return (0);
}
