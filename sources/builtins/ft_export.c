/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:11:23 by tas               #+#    #+#             */
/*   Updated: 2023/04/30 13:49:29 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

t_list	**list_ENVI;

/*TO DO
- export simple return la list par ordre aasci
- export a ---> a='' mais e s'affiche qu'avec export
- si export une var qui existe déja ça la modifie
//MODIFIER LA VAR SI ELLE EXISTE
*/


int check_equal(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

t_list  **get_list_input(t_list **list_cmd)
{
    char    *input;

    input = get_input();
    init_list(list_cmd, input);
    return (list_cmd);
}

int ft_export()
{
    t_list  **list_cmd;
    t_list  *tmp;
    
    list_cmd = malloc(sizeof(t_list));
    list_cmd[0] = NULL;
    list_cmd = get_list_input(list_cmd);
    tmp = *list_ENVI;
    if (ft_strncmp((*list_cmd)->content, "export", 6) == 1)
        return (1);
    else
    {
        (*list_cmd) = (*list_cmd)->next;
        while (*list_cmd != NULL)
        {
            if (check_equal((*list_cmd)->content) == 1)
                add_list(list_ENVI, (*list_cmd)->content);
            else
                add_list(list_ENVI, ft_strjoin((*list_cmd)->content, "="));
            (*list_cmd) = (*list_cmd)->next;
        }        
    }
    *list_ENVI = tmp;
    if (list_cmd)
        free_list(list_cmd);
    return (0);
}

// int main(int argc, char **argv, char **__environ)
// {
//     (void)argc;
//     (void)argv;
//     list_ENVI = get_list_env(__environ);
//     while(1)
//     {
//         ft_export();
//         print_list(list_ENVI);
//     }
// }
