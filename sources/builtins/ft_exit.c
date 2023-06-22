/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:02:44 by jthuysba          #+#    #+#             */
/*   Updated: 2023/06/22 20:53:53 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

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

// void    ft_putstr_fd(char *s, int fd)
// {
//     int        i;

//     i = 0;
//     if (s != NULL)
//         while (s[i])
//             write(fd, &s[i++], 1);
// }

void    ft_exit(t_minishell *data)
{
    t_list    *tmp;
    int        i;

    i = 0;
    tmp = *data->token;
    
    destroy_exec(data->x);
    
    free_list_token_content(data->token);
    free_list(data->token);
    free_list(g_list_env);
    exit(data->code_err);
    // if (ft_lstsize(*data->token) == 1)
    // {
    //     free_list_token_content(data->token);
    //     free_list(data->token);
    //     free_list(g_list_env);
    //     exit(data->code_err);
    // }
    // if (ft_lstsize(*data->token) > 2)
    // {
    //     // ft_putstr_fd2("exit\n", 2);
    //     // ft_putstr_fd2("minishell: exit: too many arguments\n", 2);
    //     free_list_token_content(data->token);
    //     free_list(data->token);
    //     free_list(g_list_env);
    //     exit(data->code_err);
    // }
    // if (ft_lstsize(*data->token) == 2)
    // {
    //     i = ft_atoi((*data->token)->next->content);
    //     // ft_putstr_fd2("exit\n", 2);
    //     free_list_token_content(data->token);
    //     free_list(data->token);
    //     free_list(g_list_env);
    //     exit(data->code_err);
    // }
    *data->token = tmp;
}
