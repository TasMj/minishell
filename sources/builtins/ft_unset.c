/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:11:35 by tas               #+#    #+#             */
/*   Updated: 2023/07/05 22:09:00 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* keep env variable's name */
static char	*var_name(char *str)
{
	char	*stockage;
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	stockage = ft_strdup_size(str, i);
	return (stockage);
}

/* check if the variable is in the env */
static int	check_var(char *str)
{
	t_list	*tmp;
	char	*var;

	tmp = *g_list_env;
	while (*g_list_env)
	{
		var = var_name((*g_list_env)->content);
		if (ft_strcmp(var, str) == 0)
		{
			*g_list_env = tmp;
			free(var);
			return (1);
		}
		free(var);
		(*g_list_env) = (*g_list_env)->next;
	}
	*g_list_env = tmp;
	return (0);
}

t_list	*to_del(char *var, char *str)
{
	t_list	*tmp_first;
	t_list	*tmp_next;
	t_list	*var_before;

	tmp_first = *g_list_env;
	while ((*g_list_env)->next != NULL && ft_strcmp(var, str) == 1)
	{
		var_before = (*g_list_env);
		(*g_list_env) = (*g_list_env)->next;
		free(var);
		var = var_name((*g_list_env)->content);
	}
	(*g_list_env) = var_before;
	if ((*g_list_env)->next->next != NULL)
		tmp_next = (*g_list_env)->next->next;
	else
		tmp_next = NULL;
	free((*g_list_env)->next->content);
	free((*g_list_env)->next);
	(*g_list_env)->next = tmp_next;
	free(var);
	return (tmp_first);
}

/* delet an environement var */
static	void	del(char *str)
{
	t_list	*tmp_first;
	char	*var;

	var = var_name((*g_list_env)->content);
	if (ft_strcmp(var, str) == 0)
	{
		tmp_first = (*g_list_env)->next;
		free((*g_list_env)->content);
		free(*g_list_env);
	}
	else
		tmp_first = to_del(var, str);
	*g_list_env = tmp_first;
}

void	write_msg(char *str)
{
	char	*msg_err;

	msg_err = ft_strjoin("unset: `", str);
	if (str[0] == '-')
	{
		singleton_minishell()->code_err = 2;
		msg_err = ft_strjoin_mod(msg_err, "': invalid option\n", 1);
		err_write(msg_err, 2);
	}
	else if (contain_exclam(str) == 1)
	{
		singleton_minishell()->code_err = 0;
		msg_err = ft_strjoin_mod(msg_err, "': event not found\n", 1);
		err_write(msg_err, 0);
	}
	else
	{
		singleton_minishell()->code_err = 1;
		msg_err = ft_strjoin_mod(msg_err, "': not a valid identifier\n", 1);
		err_write(msg_err, 1);
	}
	free(msg_err);
}

int	not_options(char *str)
{
	if (!(is_alphanum(str) == 0 && is_abc(str[0]) == 0))
	{
		write_msg(str);
		return (1);
	}
	return (0);
}

int	ft_unset(t_list **list_token)
{
	if (!(*list_token)->next)
		return (0);
	(*list_token) = (*list_token)->next;
	if (not_options((*list_token)->content) == 1)
		return (0);
	while (*list_token != NULL)
	{
		if (check_var((*list_token)->content) == 1)
			del((*list_token)->content);
		(*list_token) = (*list_token)->next;
	}
	return (0);
}
