/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:19:12 by tas               #+#    #+#             */
/*   Updated: 2023/07/01 12:46:17 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void go_to_dollar(t_substitution *s, t_minishell *data)
{
    s->deb = s->i;
    while ((*data->token)->content[s->i] && (*data->token)->content[s->i] != '$')
        s->i++;
    s->without_dollar = ft_strdup_size((*data->token)->content + s->deb, (s->i - s->deb));
	s->new_content = ft_strjoin_mod(s->new_content, s->without_dollar, 0);
    if ((*data->token)->content[s->i] && (*data->token)->content[s->i] == '$' && (*data->token)->content[s->i + 1] == '\0')
    {
        s->new_content = ft_strjoin_mod(s->new_content, "$", 0);
        s->i++;
    }
	else if ((*data->token)->content[s->i + 1] && (*data->token)->content[s->i + 1] == '?')
	{
		s->start = s->i;
        s->i+=2;
        s->end = s->i;
        s->keep_var = ft_strdup_size((*data->token)->content + s->start, (s->end - s->start));
        s->var_substitute = substitution(data, s->keep_var);
		int deb = s->i;
        s->new_content = ft_strjoin_mod(s->new_content, s->var_substitute, 3);
        while ((*data->token)->content[s->i] != '\0' && (!ft_isalnum((*data->token)->content[s->i]) && (*data->token)->content[s->i] != '$'))
               s->i++;
		char *tmp = ft_strdup_size((*data->token)->content + deb, (s->i - deb));
        s->new_content = ft_strjoin_mod(s->new_content, tmp, 3);
        free(s->keep_var);
	}
    else
    {
        s->start = s->i;
        s->i++;
        while ((*data->token)->content[s->i] != '\0' && (ft_isalnum((*data->token)->content[s->i]) || (*data->token)->content[s->i] == '_'))
            s->i++;
        s->end = s->i;
        s->keep_var = ft_strdup_size((*data->token)->content + s->start, (s->end - s->start));
        s->var_substitute = substitution(data, s->keep_var);
        if (ft_strlen(s->var_substitute) != 0)
            s->new_content = ft_strjoin_mod(s->new_content, s->var_substitute, 3);
        else
        {
			int deb = s->i;
            s->new_content = ft_strjoin_mod(s->new_content, "", 1);
            while ((*data->token)->content[s->i] != '\0' && (!ft_isalnum((*data->token)->content[s->i]) && (*data->token)->content[s->i] != '$'))
                s->i++;
			char *tmp = ft_strdup_size((*data->token)->content + deb, (s->i - deb));
            s->new_content = ft_strjoin_mod(s->new_content, tmp, 1);
        }
        free(s->keep_var);
    }
    free(s->without_dollar);
}

static void	more_dollar(t_substitution *s, t_minishell *data)
{
	s->i = 0;
	while ((*data->token)->content[s->i])
		go_to_dollar(s, data);
	free((*data->token)->content);
	(*data->token)->content = ft_strdup(s->new_content);
	free(s->new_content);
}

void	substitute_dollar(t_minishell *data)
{
	t_substitution	*s;
	t_list			*tmp;
	t_list			*prev;
	
	s = malloc(sizeof(t_substitution));
	tmp = *data->token;
	s->new_content = "";
	while ((*data->token) != NULL)
	{
		if (check_dollar((*data->token)->content) == 1)
		{
			if ((*data->token)->content[0] == 34)
			{
				printf("data: %s\n", (*data->token)->content);
				quote_sub(s, 1, data);
				printf("nim\n");
			}
			else if ((*data->token)->content[0] == 39)
			{
				printf("tas\n");
				quote_sub(s, 2, data);
			}
			else if (ft_strlen((*data->token)->content) > 1)
				more_dollar(s, data);
			else if (ft_strlen((*data->token)->content) == 1)
			{
				if (!(!(*data->token)->next && (*data->token)->content[0] == '$')
					&& (!((*data->token)->next->content && (*data->token)->content[0] == '$' && (*data->token)->next->flag_space == 1))
					&& (*data->token)->next->content && (*data->token)->content[0] == '$' && (*data->token)->next->flag_space == 0)
				{
					printf("prev: %s\n", prev->content);
					prev->next = (*data->token)->next;
					(*data->token)->next->flag_space = (*data->token)->flag_space;
					free((*data->token)->content);
					free(*data->token);
				}
			}
		}
		prev = (*data->token);
		(*data->token) = (*data->token)->next;
	}
	(*data->token) = tmp;
	free(s);
}

static void	delimit_sub(t_substitution *s, t_minishell *data)
{
	if (s->stock[s->i] && s->stock[s->i] == '$' && \
		(is_a_space(s->stock[s->i + 1]) == 1 || s->stock[s->i + 1] == '\0'))
	{
		s->new_content = ft_strjoin_mod(s->new_content, "$", 1);
		s->i++;
	}
	else if (s->stock[s->i] && s->stock[s->i + 1] && s->stock[s->i] == '$'
		&& (is_a_space(s->stock[s->i + 1]) == 0
			|| s->stock[s->i + 1] != '\0'))
	{
		s->start = s->i;
		s->i++;
		while (is_a_space(s->stock[s->i]) == 0
			&& s->stock[s->i] != '\0' && s->stock[s->i] != '$')
			s->i++;
		s->end = s->i;
		s->keep_var = ft_strdup_size(s->stock + s->start, (s->end - s->start));
		s->keep_var2 = remove_quote_end(s, data);
		if (ft_strlen(s->keep_var2) != 0)
			s->new_content = ft_strjoin_mod(s->new_content, s->keep_var2, 3);
		free(s->keep_var);
	}
}

char	*sub_quotes(char *token, t_substitution *s, t_minishell *data)
{
	s->i = 0;
	s->stock = remove_quotes(token);
	while (s->stock[s->i])
	{
		s->deb = s->i;
		while (s->stock[s->i] && s->stock[s->i] != '$')
			s->i++;
		s->without_dollar = ft_strdup_size(s->stock + s->deb, (s->i - s->deb));
		// if (!ft_strcmp(s->new_content, ""))
		// printf("without: %s\n", s->without_dollar);
		if (ft_strlen(s->new_content) == 0)
		{
			// s->new_content = ft_strjoin_mod(s->new_content, s->without_dollar, 2);
			s->new_content = ft_strdup(s->without_dollar);
			free(s->without_dollar);
		}
		else
		{
			// printf("new: [%s]\n", s->new_content);
			// printf("without: [%s]\n", s->without_dollar);
			if (!s->new_content)
				s->new_content = ft_strdup(s->without_dollar);
			else
				s->new_content = ft_strjoin_mod(s->new_content, s->without_dollar, 3);
			// s->new_content = ft_strjoin(s->new_content, s->without_dollar);
	printf("sub_quote\n");
		}
		delimit_sub(s, data);
	}
	free(s->stock);
	return (s->new_content);
}
