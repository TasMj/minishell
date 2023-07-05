/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:02:44 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/05 12:36:51 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_exit(t_minishell *data)
{
    int code;

    destroy_exec(data->x);
    free_list_token_content(data->token);
    free_list(data->token);
    free_list_token_content(g_list_env);
    free_list(g_list_env);
    code = singleton_minishell()->code_err;
    free(singleton_minishell());
    exit(code);
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
    if (data->x->nb_cmd > 1 && cmd->id == data->x->nb_cmd - 1)
        return ;
    if (is_numeric((*cmd->cmd)->next->content) == 0 || bool != 0)
    {
        printf("exit\n");
        put_str_err("minishell: exit: ");
        put_str_err((*cmd->cmd)->next->content);
        put_str_err(": numeric argument required\n");
        data->code_err = 2;
        ft_exit(data);
    }
    else if (ft_lstsize(*(cmd->cmd)) > 2)
    {
        data->code_err = 1;
        printf("exit\n");
        put_str_err("minishell: exit: too many arguments\n");
        return ;
    }
    printf("exit\n");
    ft_exit(data);
}

int	handle_exit(t_cmd *cmd, t_minishell *data)
{
	if (ft_strcmp((*cmd->cmd)->content, "exit") == 0)
	{
		if (ft_lstsize(*(cmd->cmd)) == 1 && data->x->nb_cmd == 1)
		{
			printf("exit\n");
			ft_exit(cmd->data);
		}
		else if (ft_lstsize(*(cmd->cmd)) > 1)
			ft_exit_code(cmd, data);
		return (1);
	}
	return (0);
}
