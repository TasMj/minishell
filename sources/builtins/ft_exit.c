/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:02:44 by jthuysba          #+#    #+#             */
/*   Updated: 2023/06/27 15:04:20 by jthuysba         ###   ########.fr       */
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

void    ft_exit_code(t_cmd *cmd, t_minishell *data)
{
    int code;

    if (ft_lstsize(*(cmd->cmd)) > 2)
    {
        err_msg(3);
        return ;
    }
    printf("exit\n");
    code = ft_atoi((*cmd->cmd)->next->content);
    destroy_exec(data->x);
    free_list_token_content(data->token);
    free_list(data->token);
    free_list(g_list_env);
    exit(code);
}
