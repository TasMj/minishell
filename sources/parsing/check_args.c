/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:17:01 by tas               #+#    #+#             */
/*   Updated: 2023/03/10 18:14:53 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*check si il y a une redirection < in */
int check_redir_in(char c)
{
    if (c == 60)
        return (1);
    return (0);
}

/*check si il y a une redirection > out */
int check_redir_out(char c)
{
    if (c == 62)
        return (1);
    return (0);
}

/* check si <> ou >< ou << ou >>
return err si <> ou ><, 2 si <<, 3 si >> */
int check_heredoc(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == 60)
        {
            i++;
            if (str[i] == 62)
                return (4);
            if (str[i] == 60)
                return (2);
        }
        else if (str[i] == 62)
        {
            i++;
            if (str[i] == 60)
                return (4);
            if (str[i] == 62)
                return (3);
        }
        else
            i++;
    }
    return (0);
}

/* check if there is a quote alone or <> */
int check_args(char *str)
{
    if (check_heredoc(str) == 4)
        return (1);
        // return (err_msg(0));
    if (check_pair_single_quote(str) == 1)
        return (1);
        // return (err_msg(1));
    if (check_pair_single_quote(str) == 1)
        return (1);
        // return (err_msg(1));
    return (0);
}
