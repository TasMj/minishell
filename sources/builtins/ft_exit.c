/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:02:44 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/04 11:07:59 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void    ft_putstr_fd(char *s, int fd)
// {
//     int        i;

//     i = 0;
//     if (s != NULL)
//         while (s[i])
//             write(fd, &s[i++], 1);
// }

void    ft_exit(t_minishell *data)
{
    destroy_exec(data->x);
    free_list_token_content(data->token);
    free_list(data->token);
    free_list_token_content(g_list_env);
    free_list(g_list_env);
    exit(data->code_err);
}

long long	ft_capped_atoll(const char *nptr, int *bool)
{
	int			sign;
	long long	result;

	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		++nptr;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign *= -1;
		++nptr;
	}
	result = 0;
	if (*nptr == '-' || *nptr == '+')
    	return (++*bool, 0);
    while (*nptr >= '0' && *nptr <= '9')
	{
		if (sign > 0 && (LLONG_MAX - *nptr + '0') / 10 < result)
			return (++*bool, 0);
		if (sign < 0 && (LLONG_MIN + *nptr - '0') / 10 > -result)
			return (++*bool, 0);
		result = 10 * result + *nptr - '0';
		nptr++;
	}
	return (sign * result);
}

void    ft_exit_code(t_cmd *cmd, t_minishell *data)
{
    int			bool;

    bool = 0;
	data->code_err = ft_capped_atoll((*cmd->cmd)->next->content, &bool);
    if (is_numeric((*cmd->cmd)->next->content) == 0 || bool != 0)
    {
        printf("exit\n");
        // err_write("exit: numeric argument required\n", 1);
        put_str_err("minishell: exit: ");
        put_str_err((*cmd->cmd)->next->content);
        put_str_err(": numeric argument required\n");
        data->code_err = 2;
        ft_exit(data);
    }
    else if (ft_lstsize(*(cmd->cmd)) > 2)
    {
        printf("exit\n");
        err_msg(3, "IGNORE", 1);
        return ;
    }
    printf("exit\n");
    ft_exit(data);
}
