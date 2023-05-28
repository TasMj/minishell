/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:02:44 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/28 01:56:30 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atoi(const char *nptr)
{
	long long	res;
	int			i;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if ((res > 2147483647 && sign == 1) || (res < -2147483648 && sign == -1))
			return (-1);
		res = (res * 10) + (nptr[i] - 48);
		i++;
	}
	return (res * sign);
}

void    ft_putstr_fd2(char *s, int fd)
{
    int        i;

    i = 0;
    if (s != NULL)
        while (s[i])
            write(fd, &s[i++], 1);
}

void    ft_exit(t_list **lst)
{
    t_list    *tmp;
    int        i;

    i = 0;
    tmp = *lst;
    if (ft_lstsize(*lst) == 1)
    {
        ft_putstr_fd2("exit\n", 2);
        exit(0);
    }
    if (ft_lstsize(*lst) > 2)
    {
        ft_putstr_fd2("exit\n", 2);
        ft_putstr_fd2("minishell: exit: too many arguments\n", 2);
        exit(1);
    }
    if (ft_lstsize(*lst) == 2)
    {
        i = ft_atoi((*lst)->next->content);
        ft_putstr_fd2("exit\n", 2);
        exit(i);
    }
    *lst = tmp;
}
