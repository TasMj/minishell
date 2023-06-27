/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:02:44 by jthuysba          #+#    #+#             */
/*   Updated: 2023/06/27 11:00:00 by tas              ###   ########.fr       */
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
    // t_list    *tmp;
    // int        i;

    // i = 0;
    // tmp = *data->token;
    
    destroy_exec(data->x);
    
    free_list_token_content(data->token);
    free_list(data->token);
    free_list(g_list_env);

    exit(data->code_err);
    // if (ft_lstsize(*da1ta->token) == 1)
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
    // *data->token = tmp;
}
