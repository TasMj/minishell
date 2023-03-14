/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntactic_analisis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:19:12 by tas               #+#    #+#             */
/*   Updated: 2023/03/14 02:20:52 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *remove_bracket(char *str)
{
    // int i;
    char *new_str;
    
    new_str = ft_strdup_size(str + 1, ft_strlen(str) - 2);
    
    // i = 1;
    // new_str = malloc(sizeof(char) * (ft_strlen(str) - 2) + 1);
    // while (i < ft_strlen(str) - 1)
    // {
        // printf("ns: %c\n", str[i]);
        // new_str[i] = str[i];
		// i++;
    // }
    // new_str[i] = '\0';
    printf("[%s] sans brackets: [%s]\n", str, new_str);
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

char    *remove_space(char *str)
{
    int i;
    int start;
    int end;
    char *stockage;

    i = 0;
    while (is_a_separator(str[i]) == 1)
        i++;
    start = i;
    while (is_a_separator(str[i]) == 0)
        i++;
    end = i;
    stockage = ft_strdup_size(str + start, (end - start));
    return (stockage);
}

char    *substitution(char *token)
{
    char    *variable;
    
    printf("TOKEN: %s   ", token + 1);
    // variable = malloc(sizeof(char) * ft_strlen(getenv(token + 1) + 1));
    variable = getenv(token + 1);
    printf("VARIABLE: %s\n", variable);
    
    if (!variable)
        return(NULL);
    return (variable);
}

void    substitute_dollar(t_list **list_token)
{
    char    *var_substitute;
    t_list  *tmp;
    
    printf("--------------------------------------------\n");
    
    tmp = *list_token;
    while ((*list_token) != NULL)
    {
        if (check_dollar((*list_token)->content) == 1)
        {
            if ((*list_token)->content[0] == 34 || (*list_token)->content[0] == 39)
            {
                var_substitute = sub_brackets((*list_token)->content);
                free((*list_token)->content);
                (*list_token)->content = ft_strdup_size(var_substitute, ft_strlen(var_substitute));
            }
            else if (ft_strlen((*list_token)->content) > 1)
            {
                var_substitute = substitution((*list_token)->content);
                printf("var: [%s]\n", var_substitute);
                if (!var_substitute)
                {
                    // ft_lstdelone(list_token, (*list_token), del);
                    //mettre une var NULL
                }
                free ((*list_token)->content);
                (*list_token)->content = ft_strdup_size(var_substitute, ft_strlen(var_substitute));
            }
        }
        printf("sub done: [%s]\n", (*list_token)->content);
        // printf("first: [%s]\n", (*list_token)->premier->content);
        
        (*list_token) = (*list_token)->next;

    }
    *list_token = tmp;  
    
}


char    *sub_brackets(char *token)
{
    int i;
    int start;
    int end;
    int deb;
    char *stockage;
    char *without_dollar;
    char *keep_var;
    char *keep_var2;
    char    *new_content;
    
    i = 0;
    new_content = "";
    stockage = remove_bracket(token);
    while (stockage[i])
    {
        deb = i;
        while (stockage[i] && stockage[i] != '$')
            i++;
        without_dollar = ft_strdup_size(stockage + deb, (i - deb));
        new_content = ft_strjoin_mod(new_content, without_dollar, 2);
        if (stockage[i] && stockage[i] == '$' && (is_a_separator(stockage[i + 1]) == 1 || stockage[i + 1] == '\0'))
        {
            new_content = ft_strjoin_mod(new_content, "$", 1);
            i++;
        }
        else if (stockage[i] && stockage[i + 1] && stockage[i] == '$' && (is_a_separator(stockage[i + 1]) == 0 || stockage[i + 1] != '\0'))
        {
            start = i;
            i++;
            while (is_a_separator(stockage[i]) == 0 && stockage[i] != '\0' && stockage[i] != '$')
                i++;
            end = i;
            keep_var = ft_strdup_size(stockage + start, (end - start));
            keep_var2 = ft_strdup_size(substitution(keep_var), ft_strlen(keep_var));
            new_content = ft_strjoin_mod(new_content, keep_var2, 2);
        }
    }
    return (new_content);
}

    
    // tab_dollar = ft_split((*list_token)->content, '$');
    //         else
    //         tab_dollar = ft_split(remove_bracket((*list_token)->content), '$');
    //         while (tab_dollar[i])
    //         {
    //             printf("tab: [%s]\n", tab_dollar[i]);
    //             var_substitute = substitution(tab_dollar[i]);
    //             printf("var: [%s]\n", var_substitute);
    //             new_content = ft_strjoin_mod(new_content, var_substitute, 0);
    //             printf("new: [%s]\n", new_content);
    //             i++;
    //         }
    //         free ((*list_token)->content);
    //         (*list_token)->content = ft_strdup_size(new_content, ft_strlen(new_content));
    //     }
    //     printf("sub done: [%s]\n", (*list_token)->content);
        

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
