/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntactic_analisis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:19:12 by tas               #+#    #+#             */
/*   Updated: 2023/03/12 18:01:36 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *remove_bracket(char *str)
{
    int i;
    char *new_str;
    
    i = 1;
    new_str = malloc(sizeof(char) * (ft_strlen(str) - 2));
    while (i < ft_strlen(str) - 1)
    {
        new_str[i] = str[i];
		i++;
    }
    new_str[i] = '\0';
    return (new_str);
}

int check_dollar(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '$')
            return (1);
        i++;
    }
    return (0);
}

char    *substitution(char *token)
{
    char    *variable;
    
    printf("TOKEN: %s\n", token);
    variable = getenv(token);
    printf("VARIABLE: %s\n", variable);
    
    if (!variable)
        return(token);
    return (variable);
}

void    substitute_dollar(t_list **list_token)
{
    int i = 0;
    char **tab_dollar;
    char    *var_substitute;
    char    *new_content;
    
printf("--------------------------------------------\n");
    
    new_content = "";
    
    while ((*list_token) != NULL)
    {
        printf("content:       %s\n", (*list_token)->content);
        if (check_dollar((*list_token)->content) == 1)
        {
            // printf("[%s]\n", remove_bracket((*list_token)->content));
            // if ((*list_token)->content[0] == 34 || (*list_token)->content[0] == 39)
                // tab_dollar = ft_split(remove_bracket((*list_token)->content), '$');
            // else
            tab_dollar = ft_split((*list_token)->content, '$');
            while (tab_dollar[i])
            {
                var_substitute = substitution(tab_dollar[i]);
                printf("var: %s\n", var_substitute);
                new_content = ft_strjoin_mod(new_content, var_substitute, 0);
                printf("new: %s\n", new_content);
                i++;
            }
            free ((*list_token)->content);
            (*list_token)->content = ft_strdup_size(new_content, ft_strlen(new_content));
        }
        printf("sub done: %s\n", (*list_token)->content);
        (*list_token) = (*list_token)->next;
    }
}


/* determine the command type*/
void    get_type(t_list *list_token)
{
    if (is_word((*list_token).content) == 1) // add our own builtin
        (*list_token).type = WORD;
    else if (determine_type((*list_token).content) == 1)
        (*list_token).type = HEREDOC;
    else if (determine_type((*list_token).content) == 2)
        (*list_token).type = APPEND;
    else if (determine_type((*list_token).content) == 3)
        (*list_token).type = STDIN;
    else if (determine_type((*list_token).content) == 4)
        (*list_token).type = STDOUT;
    else if (determine_type((*list_token).content) == 5)
        (*list_token).type = PIPE;
    else if (determine_type((*list_token).content) == 6)
        (*list_token).type = END;
}
