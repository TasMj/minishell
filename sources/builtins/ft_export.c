/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:11:23 by tas               #+#    #+#             */
/*   Updated: 2023/07/10 22:49:57 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* sort the environement by ascii */
static int	sort_env_ascii(t_minishell *data)
{
	t_list	**copy;

	copy = malloc(sizeof(t_list));
	if (!copy)
		return (1);
	ft_memset(copy, 0, sizeof(t_list));
	copy = ft_copy_list(copy, data);
	copy = sort_env(copy);
	print_export(copy);
	free_list(copy);
	return (0);
}

/* add new variable to the environement */
int	add_var_env(char *stock, t_list *tmp, t_minishell *data)
{
	char	*copy;
	char	*msg_err;

	(void)tmp;
	msg_err = NULL;
	if (stock[0] == '=')
	{
		err_write("export: `=': not a valid identifier\n", 1);
		free(stock);
		return (1);
	}
	copy = del_equal(stock);
	if (!(is_alphanum(copy) == 0 && is_abc(copy[0]) == 0))
	{
		err_add_env(msg_err, stock, copy);
		return (1);
	}
	if (contain_exclam(stock) == 1)
	{
		err_exclam(msg_err, stock, copy);
		return (1);
	}
	add_list(data->env, stock, 0);
	free(copy);
	return (0);
}

/* modify the value of an environement arg that already exist */
int	modify_var(char *stock, t_list *tmp, t_minishell *data)
{
	char	*copy_env;
	char	*copy_token;

	while (*data->env)
	{
		copy_env = del_equal((*data->env)->content);
		copy_token = del_equal(stock);
		if (ft_strcmp(copy_env, copy_token) == 1)
			(*data->env) = (*data->env)->next;
		else if (ft_strcmp(copy_env, copy_token) == 0)
		{
			free((*data->env)->content);
			(*data->env)->content = ft_strdup(stock);
			*data->env = tmp;
			free(copy_env);
			free(copy_token);
			return (1);
		}
		free(copy_env);
		free(copy_token);
	}
	return (0);
}

static	char	*extract_stock(t_list **list_token)
{
	char	*stock;

	stock = NULL;
	(*list_token) = (*list_token)->next;
	stock = set_stock((*list_token)->content, stock);
	(*list_token) = (*list_token)->next;
	while (*list_token && (*list_token)->content[0] != '='
		&& (*list_token)->flag_space == 0)
	{
		if (*list_token && ft_strlen((*list_token)->content) == 0)
			(*list_token) = (*list_token)->next;
		else
		{
			stock = ft_strjoin_mod(stock, (*list_token)->content, 1);
			(*list_token) = (*list_token)->next;
		}
	}
	return (stock);
}

int	ft_export(t_list **list_token, t_minishell *data)
{
	t_list	*tmp;
	char	*stock;
	char	*copy;

	tmp = *data->env;
	if (ft_lstsize(*list_token) == 1)
	{
		if (sort_env_ascii(data) != 0)
			return (1);
	}
	else
	{
		while (*list_token != NULL)
		{
			stock = extract_stock(list_token);
			copy = del_equal(stock);
			if (add_modif(copy, stock, tmp, data) == 0)
				return (0);
			(*list_token) = (*list_token)->next;
		}
	}
	*data->env = tmp;
	return (0);
}
