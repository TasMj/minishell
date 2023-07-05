/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:47:38 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/05 09:55:31 by jthuysba         ###   ########.fr       */
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

static char	*remove_dollar(char *str)
{
	int		i;
	int		j;
	char	*token;

	i = 0;
	j = 0;
	if (str[i])
	{
		i++;
		token = malloc(sizeof(char) * ft_strlen(str));
	}
	else 
		return (NULL);
	while(str[i])
	{
		token[j] = str[i];
		i++;
		j++;
	}
	token[j] = '\0';
	return(token);
	
}

char *substitution(t_minishell *data, char *token)
{
	char *variable;
	
	variable = NULL;
	if ((ft_strlen(token) == 2) && ft_strcmp(token, "$?") == 0)
		variable = ft_itoa(data->code_err);
	else if (token[0] == '$')
	{
		char *var_check = remove_dollar(token);
		if (is_in_env(var_check))
			variable = get_venv(var_check);
		else
			variable = "";
		free(var_check);
	}
	else if (!variable)
		variable = "";
	return (variable);
}

void quote_sub(t_substitution *s, int a, t_minishell *data)
{
	if (a == 1)
		s->var_substitute = sub_quotes((*data->token)->content, s, data);
	else if (a == 2)
		s->var_substitute = remove_quotes((*data->token)->content);
	free((*data->token)->content);
	(*data->token)->content = ft_strdup(s->var_substitute);
	(*data->token)->flag_quote = 1;
	free(s->var_substitute);
}

char *remove_quote_end(t_substitution *s, t_minishell *data)
{
	int i;
	char *tmp;

	i = 1;
	tmp = NULL;
	if (ft_strncmp(s->keep_var, "$?", 2) == 0)
		s->var_substitute = substitution(data, "$?");
	else
	{
		while (ft_isalnum(s->keep_var[i]))
			i++;
		s->end = i;
		s->keep_var2 = ft_strdup_size(s->keep_var, s->end);
		s->var_substitute = substitution(data, s->keep_var2);
		free(s->keep_var2);
	}
	if (s->keep_var[s->end] != '\0')
	{
		s->start = s->end;
		while (s->keep_var[s->end] != '\0')
			s->end++;
		tmp = ft_strdup_size(s->keep_var + s->start, (s->end - s->start));
		tmp = ft_strjoin_mod(s->var_substitute, tmp, 2);
	}
	else
		tmp = ft_strdup(s->var_substitute);
	if (ft_strlen(s->var_substitute) > 0)
		free(s->var_substitute);
	return (tmp);
}

void	hdoc_exclam(t_substitution *s, char *str, t_minishell *data)
{
	s->start = s->i;
    s->i += 2;
    s->end = s->i;
    s->keep_var = ft_strdup_size(str + s->start, (s->end - s->start));
    s->var_substitute = substitution(data, s->keep_var);
	int deb = s->i;
    s->new_content = ft_strjoin_mod(s->new_content, s->var_substitute, 3);
    while (str[s->i] != '\0' && (!ft_isalnum(str[s->i]) && str[s->i] != '$'))
           s->i++;
	char *tmp = ft_strdup_size(str + deb, (s->i - deb));
    s->new_content = ft_strjoin_mod(s->new_content, tmp, 3);
    free(s->keep_var);
}

void	hdoc_rest(t_substitution *s, char *str, t_minishell *data)
{
	s->start = s->i;
	if ((s->i + 1) < ft_strlen((*data->token)->content))
	    s->i++;
    while (str[s->i] != '\0' && (ft_isalnum(str[s->i]) || str[s->i] == '_'))
        s->i++;
    s->end = s->i;
    s->keep_var = ft_strdup_size(str + s->start, (s->end - s->start));
    s->var_substitute = substitution(data, s->keep_var);
    if (ft_strlen(s->var_substitute) != 0)
        s->new_content = ft_strjoin_mod(s->new_content, s->var_substitute, 3);
    else
    {
		int deb = s->i;
        s->new_content = ft_strjoin_mod(s->new_content, "", 1);
        while (str[s->i] != '\0' && (!ft_isalnum(str[s->i]) && str[s->i] != '$'))
            s->i++;
		char *tmp = ft_strdup_size(str + deb, (s->i - deb));
        s->new_content = ft_strjoin_mod(s->new_content, tmp, 3);
    }
    if (s->keep_var)
		free(s->keep_var);
}

void sub_dollar_hdoc(t_substitution *s, char *str, t_minishell *data)
{
    s->deb = s->i;
    while (str[s->i] && str[s->i] != '$')
        s->i++;
    s->without_dollar = ft_strdup_size(str + s->deb, (s->i - s->deb));
	if (!s->new_content)
		s->new_content = ft_strdup(s->without_dollar);
	else
		s->new_content = ft_strjoin_mod(s->new_content, s->without_dollar, 1);
    if (str[s->i] && str[s->i] == '$' && str[s->i + 1] == '\0')
    {
        s->new_content = ft_strjoin_mod(s->new_content, "$", 0);
        s->i++;
    }
	else if (str[s->i] && str[s->i + 1] && str[s->i + 1] == '?')
		hdoc_exclam(s, str, data);
    else
    {
        s->start = s->i;
		if ((s->i + 1) < ft_strlen((*data->token)->content))
	        s->i++;
        while ((s->i <= ft_strlen(str)) && str[s->i] != '\0' && (ft_isalnum(str[s->i]) || str[s->i] == '_'))
            s->i++;
        s->end = s->i;
        s->keep_var = ft_strdup_size(str + s->start, (s->end - s->start));
        s->var_substitute = substitution(data, s->keep_var);
        if (s->var_substitute && ft_strlen(s->var_substitute) != 0)
            s->new_content = ft_strjoin_mod(s->new_content, s->var_substitute, 3);
        else
        {
			int deb = s->i;
            s->new_content = ft_strjoin_mod(s->new_content, "", 1);
            while ((s->i <= ft_strlen(str)) && str[s->i] != '\0' && (!ft_isalnum(str[s->i]) && str[s->i] != '$'))
                s->i++;
			char *tmp = ft_strdup_size(str + deb, (s->i - deb));
            s->new_content = ft_strjoin_mod(s->new_content, tmp, 3);
        }
        if (s->keep_var)
			free(s->keep_var);
    }
	if (s->without_dollar)
	    free(s->without_dollar);
}