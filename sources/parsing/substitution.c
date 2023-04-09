/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:19:12 by tas               #+#    #+#             */
/*   Updated: 2023/04/09 12:42:38 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    while (is_a_space(str[i]) == 1)
        i++;
    start = i;
    while (is_a_space(str[i]) == 0)
        i++;
    end = i;
    stockage = ft_strdup_size(str + start, (end - start));
    return (stockage);
}

char    *substitution(char *token)
{
    char    *variable;
    
    variable = getenv(token + 1);
    if (!variable)
    {
        variable = malloc(1);
        variable = "";
    }
    return (variable);
}

void    quote_sub(t_substitution *s, t_list *list_token, int a)
{
    if (a == 1)
        s->var_substitute = sub_quotes(list_token->content, s);
    else if (a == 2)
        s->var_substitute = remove_quotes(list_token->content);
    free(list_token->content);
    list_token->content = ft_strdup_size(s->var_substitute, ft_strlen(s->var_substitute));
}

void    go_to_dollar(t_substitution *s, t_list *list_token)
{
    s->deb = s->i;
    while (list_token->content[s->i] && list_token->content[s->i] != '$')
        s->i++;
    s->without_dollar = ft_strdup_size(list_token->content + s->deb, (s->i - s->deb));
    s->new_content = ft_strjoin_mod(s->new_content, s->without_dollar, 2);
    if (list_token->content[s->i] && list_token->content[s->i] == '$' && list_token->content[s->i + 1] == '\0')
    {
        s->new_content = ft_strjoin_mod(s->new_content, "$", 0);
        s->i++;
    }
    else
    {
        s->start = s->i;
        s->i++;
        while (list_token->content[s->i] != '\0' && list_token->content[s->i] != '$')
            s->i++;
        s->end = s->i;
        s->keep_var = ft_strdup_size(list_token->content + s->start, (s->end - s->start));
        s->var_substitute = ft_strdup_size(substitution(s->keep_var), ft_strlen(substitution(s->keep_var)));
        s->new_content = ft_strjoin_mod(s->new_content, s->var_substitute, 2);
    }
}

void    substitute_dollar(t_list **list_token)
{
    t_substitution  *s;
    t_list  *tmp;
    
    s = malloc(sizeof(t_substitution));
    tmp = *list_token;
    s->new_content = "";
    while ((*list_token) != NULL)
    {
        if (check_dollar((*list_token)->content) == 1)
        {
            if ((*list_token)->content[0] == 34)
                quote_sub(s, (*list_token), 1);
            else if ((*list_token)->content[0] == 39) //single quote
                quote_sub(s, (*list_token), 2);
            else if (ft_strlen((*list_token)->content) > 1)
            {
                s->i = 0;
                s->new_content = "";
                while ((*list_token)->content[s->i])
                    go_to_dollar(s, (*list_token));
                free((*list_token)->content);
                (*list_token)->content = ft_strdup_size(s->new_content, ft_strlen(s->new_content));
                free(s->new_content);
            }
        }
        (*list_token) = (*list_token)->next;
    }
    *list_token = tmp;  
}

char    *sub_quotes(char *token, t_substitution *s)
{
    s->i = 0;
    s->new_content = "";
    s->stockage = remove_quotes(token);
    while (s->stockage[s->i])
    {
        s->deb = s->i;
        while (s->stockage[s->i] && s->stockage[s->i] != '$')
            s->i++;
        s->without_dollar = ft_strdup_size(s->stockage + s->deb, (s->i - s->deb));
        s->new_content = ft_strjoin_mod(s->new_content, s->without_dollar, 2);
        if (s->stockage[s->i] && s->stockage[s->i] == '$' && (is_a_space(s->stockage[s->i + 1]) == 1 || s->stockage[s->i + 1] == '\0'))
        {
            s->new_content = ft_strjoin_mod(s->new_content, "$", 1);
            s->i++;
        }
        else if (s->stockage[s->i] && s->stockage[s->i + 1] && s->stockage[s->i] == '$' && (is_a_space(s->stockage[s->i + 1]) == 0 || s->stockage[s->i + 1] != '\0'))
        {
            s->start = s->i;
            s->i++;
            while (is_a_space(s->stockage[s->i]) == 0 && s->stockage[s->i] != '\0' && s->stockage[s->i] != '$')
                s->i++;
            s->end = s->i;
            s->keep_var = ft_strdup_size(s->stockage + s->start, (s->end - s->start));
            s->keep_var2 = ft_strdup_size(substitution(s->keep_var), ft_strlen(substitution(s->keep_var)));
            s->new_content = ft_strjoin_mod(s->new_content, s->keep_var2, 2);
        }
    }
    return (s->new_content);
}
