/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:02:44 by jthuysba          #+#    #+#             */
/*   Updated: 2023/06/30 21:06:41 by tas              ###   ########.fr       */
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
    long long	code;
    int			bool;

    bool = 0;
	code = ft_capped_atoll((*cmd->cmd)->next->content, &bool);
    if (is_numeric((*cmd->cmd)->next->content) == 0 || bool != 0)
    {
        // printf("minishell: exit: %s: numeric argument required\n", (*cmd->cmd)->next->content);
        err_write("exit: numeric argument required\n", 1);
        code = 2;
    }
    else if (ft_lstsize(*(cmd->cmd)) > 2)
    {
        err_msg(3, "IGNORE", 1);
        return ;
    }
    printf("exit\n");
    destroy_exec(data->x);
    free_list_token_content(data->token);
    free_list(data->token);
    free_list(g_list_env);
    exit(code);
}
