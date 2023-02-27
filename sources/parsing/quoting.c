/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 16:15:52 by tmejri            #+#    #+#             */
/*   Updated: 2023/02/27 12:02:11 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

/*Return 1 if the command line contain a quote, 0 if not */
int contain_a_quote(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '|' || str[i] == '&' || str[i] == ';' || str[i] == '<'
            || str[i] == '>' || str[i] == '(' || str[i] == ')' || str[i] == '$'
            || str[i] == '`' || str[i] == 92 || str[i] == 34 || str[i] == 39
            || str[i] == 32 || str[i] == 9 || str[i] == 10)
                return (1);
        i++;
    }
    return (0);
}

/*PB CAR NE LIS PAS LES QUOTES*/
/* check si après la première quote (", ') on trouve la deuxième
return 1 si "", 2 si '', 0 sinon */
int check_peer_quote(char *str)
{
    int i;
    int flag;

    i = 0;    
    flag = 0;
    while (str[i])
    {
        if (str[i] == 34) //"
        {
            flag = 1;
            while(str[i])
            {
                i++;
                if (str[i] == 34 && flag == 1)
                    return(1); //en attendant de savoir quoi coder
            }
            return (3);
        }
        else if (str[i] == 39) //'
        {
            flag = 1;
            while(str[i])
            {
                i++;
                if (str[i] == 39 && flag == 1)
                    return(2); //en attendant de savoir quoi coder
            }
            return (3);
        }
        i++;
    }
    return (0);
}

// #include <stdio.h>
// int main(int argc, char **argv)
// {
    // (void)argc;
    // printf("%d\n", check_peer_quote(argv[1]));
    // printf("%d\n", contain_a_quote(argv[1]));
// }
