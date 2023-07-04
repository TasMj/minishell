/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:19:12 by tas               #+#    #+#             */
/*   Updated: 2023/07/04 21:16:17 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void go_to_dollar(t_substitution *s, t_minishell *data)
{
    s->deb = s->i;
    while ((*data->token)->content[s->i] && (*data->token)->content[s->i] != '$')
        s->i++;
    s->without_dollar = ft_strdup_size((*data->token)->content + s->deb, (s->i - s->deb));
	if (!s->new_content)
		s->new_content = ft_strdup(s->without_dollar);
	else
		s->new_content = ft_strjoin_mod(s->new_content, s->without_dollar, 1);
    if ((*data->token)->content[s->i] && (*data->token)->content[s->i] == '$' && (*data->token)->content[s->i + 1] == '\0')
    {
        s->new_content = ft_strjoin_mod(s->new_content, "$", 0);
        s->i++;
    }
	else if ((*data->token)->content[s->i] && (*data->token)->content[s->i + 1] && (*data->token)->content[s->i + 1] == '?')
	{
		s->start = s->i;
        s->i += 2;
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
		if ((s->i + 1) < ft_strlen((*data->token)->content))
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
            s->new_content = ft_strjoin_mod(s->new_content, tmp, 3);
        }
        if (s->keep_var)
			free(s->keep_var);
    }
	if (s->without_dollar)
	    free(s->without_dollar);
}

t_list	*ft_lst_prev(t_list *elem, t_list *first)
{
	t_list	*tmp;

	tmp = first;
	if (first == elem)
		return (NULL);
	while (first)
	{
		if (first->next == elem)
		{
			first = tmp;
			return (first);
		}
		first = first->next;
	}
	first = tmp;	
	// printf("ret: %s\n", first->content);
	return (NULL);
}

static void	more_dollar(t_substitution *s, t_minishell *data)
{
	s->i = 0;
	while ((*data->token)->content[s->i])
		go_to_dollar(s, data);
	free((*data->token)->content);
	(*data->token)->content = ft_strdup(s->new_content);
}

void	substitute_dollar(t_minishell *data)
{
	t_substitution	*s;
	t_list			*tmp;
	t_list			*prev;
	t_list	*start;
	t_list	*reset;

	start = *data->token;
	reset = *data->token;
	s = malloc(sizeof(t_substitution));
	ft_memset(s, 0, sizeof(t_substitution));
	tmp = *data->token;
	prev = NULL;
	while ((*data->token) != NULL)
	{
		s->new_content = NULL;
		if (check_dollar((*data->token)->content) == 1)
		{
			if ((*data->token)->content[0] == 34)
				quote_sub(s, 1, data);
			else if ((*data->token)->content[0] == 39)
				quote_sub(s, 2, data);
			else if (ft_strlen((*data->token)->content) > 1)
			{
				if (ft_lst_prev(*data->token, start) == NULL)
				{
					// printf("1\n");
					start = reset;
					more_dollar(s, data);
				}
				else if (ft_lst_prev(*data->token, start) != NULL && ft_lst_prev(*data->token, start)->type != HEREDOC)
				{
					start = reset;
					more_dollar(s, data);
				}
				// more_dollar(s, data);
			}
			else if (ft_strlen((*data->token)->content) == 1)
			{
				if (!(!(*data->token)->next && (*data->token)->content[0] == '$')
					&& (!((*data->token)->next->content && (*data->token)->content[0] == '$' && (*data->token)->next->flag_space == 1))
					&& (*data->token)->next->content && (*data->token)->content[0] == '$' && (*data->token)->next->flag_space == 0)
				{
					if (prev != NULL)
					{
						prev->next = (*data->token)->next;
						(*data->token)->next->flag_space = (*data->token)->flag_space;
						free((*data->token)->content);
						free(*data->token);
						(*data->token) = prev;
					}
					else
					{
						tmp = (*data->token)->next;
						free ((*data->token)->content);
						free(*data->token);
						(*data->token) = tmp;
					}
				}
			}
		}
		if (s->new_content)
			free(s->new_content);
		prev = (*data->token);
		(*data->token) = (*data->token)->next;
	}
	*data->token = tmp;
	free(s);
}

static void	delimit_sub(t_substitution *s, t_minishell *data)
{
	if (s->stock[s->i] && s->stock[s->i] == '$' && (is_a_space(s->stock[s->i + 1]) == 1 || s->stock[s->i + 1] == '\0'))
	{
		s->new_content = ft_strjoin_mod(s->new_content, "$", 1);
		s->i++;
	}
	else if (s->stock[s->i] && s->stock[s->i] == '$' && s->stock[s->i + 1] && s->stock[s->i + 1] == '?')
	{
		s->start = s->i;
        s->i += 2;
        s->end = s->i;
        s->keep_var = ft_strdup_size(s->stock + s->start, (s->end - s->start));
        s->keep_var2 = remove_quote_end(s, data);
		int deb = s->i;
        s->new_content = ft_strjoin_mod(s->new_content, s->keep_var2, 3);
        while (s->stock[s->i] != '\0' && (!ft_isalnum(s->stock[s->i]) && s->stock[s->i] != '$'))
               s->i++;
		char *tmp = ft_strdup_size(s->stock + deb, (s->i - deb));
        s->new_content = ft_strjoin_mod(s->new_content, tmp, 3);
        free(s->keep_var);
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
		else
			free(s->keep_var2);
		free(s->keep_var);
	}
}

char	*sub_quotes(char *token, t_substitution *s, t_minishell *data)
{
	char	*to_return;
	
	s->i = 0;
	s->stock = remove_quotes(token);
	while (s->stock[s->i])
	{
		s->deb = s->i;
		while (s->stock[s->i] && s->stock[s->i] != '$')
			s->i++;
		s->without_dollar = ft_strdup_size(s->stock + s->deb, (s->i - s->deb));
		if (!s->new_content)
		{
			if (s->without_dollar)
			{
				s->new_content = ft_strdup(s->without_dollar);
				free(s->without_dollar);
			}
		}
		else
		{
			if (s->without_dollar)
				s->new_content = ft_strjoin_mod(s->new_content, s->without_dollar, 3);
		}
		delimit_sub(s, data);
	}
	free(s->stock);
	to_return = ft_strdup(s->new_content);
	return (to_return);
}
