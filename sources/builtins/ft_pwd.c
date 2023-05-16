/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:10:29 by tas               #+#    #+#             */
/*   Updated: 2023/04/30 13:47:46 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pwd(void)
{
    char    cwd[1024];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("getcwd() error");
}

// int main(int argc, char **argv, char **env)
// {
//     (void)argc;
//     (void)argv;
//     (void)env;
    
//     ft_pwd();
//     return (0);
// }
