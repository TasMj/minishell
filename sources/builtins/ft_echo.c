/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:09:31 by tas               #+#    #+#             */
/*   Updated: 2023/04/30 13:35:43 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TO DO
- enlever le break
- voir si besoin de free stockage et si c'est ok de mettre ""
*/

int ft_echo(void)
{
    t_list  **list_cmd;
    t_list  *tmp;
    char    *input;
    char    *stockage;
    int     flag;
    int     to_free;

    flag = 0;
    to_free = 0;
    input = get_input();
    list_cmd = malloc(sizeof(t_list));
    list_cmd[0] = NULL;
    init_list(list_cmd, input);
    stockage = NULL;
    stockage = "";
    tmp = *list_cmd;
    while ((*list_cmd) != NULL)
    {
		if (ft_strncmp((*list_cmd)->content, "echo", 4) == 0 && (*list_cmd)->next != NULL)
        {
            (*list_cmd) = (*list_cmd)->next;
    		if (ft_strncmp((*list_cmd)->content, "-n", 2) == 0)
            {
                flag = 1;
                if ((*list_cmd)->next == NULL)
                    break;
                (*list_cmd) = (*list_cmd)->next;
            }
            while (*list_cmd)
            {
                to_free = 1;
                stockage = ft_strjoin(stockage, (*list_cmd)->content);
                if ((*list_cmd)->next != NULL)
                    stockage = ft_strjoin(stockage, " ");
                (*list_cmd) = (*list_cmd)->next;
            }
        }
        else
            (*list_cmd) = (*list_cmd)->next;
    }
    (*list_cmd) = tmp;
    if (flag != 1)
        printf("%s\n", stockage);
    else
        printf("%s", stockage);
    if (to_free == 1)
        free(stockage);
    if (list_cmd)
        free_list(list_cmd);
    if (input)
        free(input);
    return (0);
}

// int main(int argc, char **argv, char **env)
// {
//     (void)argc;
//     (void)argv;
//     (void)env;
    
//     ft_echo();
//     return (0);
// }
