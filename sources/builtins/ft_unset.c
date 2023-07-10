/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:11:35 by tas               #+#    #+#             */
/*   Updated: 2023/07/10 22:18:14 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*to_del(char *var, char *str, t_minishell *data)
{
	t_list	*tmp_first;
	t_list	*tmp_next;
	t_list	*var_before;

	tmp_first = *data->env;
	while ((*data->env)->next != NULL && ft_strcmp(var, str) == 1)
	{
		var_before = (*data->env);
		(*data->env) = (*data->env)->next;
		free(var);
		var = var_name((*data->env)->content);
	}
	(*data->env) = var_before;
	if ((*data->env)->next->next != NULL)
		tmp_next = (*data->env)->next->next;
	else
		tmp_next = NULL;
	free((*data->env)->next->content);
	free((*data->env)->next);
	(*data->env)->next = tmp_next;
	free(var);
	return (tmp_first);
}

/* delet an environement var */
static	void	del(char *str, t_minishell *data)
{
	t_list	*tmp_first;
	char	*var;

	var = var_name((*data->env)->content);
	if (ft_strcmp(var, str) == 0)
	{
		tmp_first = (*data->env)->next;
		free((*data->env)->content);
		free(*data->env);
	}
	else
		tmp_first = to_del(var, str, data);
	*data->env = tmp_first;
}

void	write_msg(char *str)
{
	char	*msg_err;

	msg_err = ft_strjoin("unset: `", str);
	if (str[0] == '-')
	{
		g_exit_code = 2;
		msg_err = ft_strjoin_mod(msg_err, "': invalid option\n", 1);
		err_write(msg_err, 2);
	}
	else if (contain_exclam(str) == 1)
	{
		g_exit_code = 0;
		msg_err = ft_strjoin_mod(msg_err, "': event not found\n", 1);
		err_write(msg_err, 0);
	}
	else
	{
		g_exit_code = 1;
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

int	ft_unset(t_list **list_token, t_minishell *data)
{
	if (!(*list_token)->next)
		return (0);
	(*list_token) = (*list_token)->next;
	if (not_options((*list_token)->content) == 1)
		return (0);
	while (*list_token != NULL)
	{
		if (check_var((*list_token)->content, data) == 1)
			del((*list_token)->content, data);
		(*list_token) = (*list_token)->next;
	}
	return (0);
}
