/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:11:23 by tas               #+#    #+#             */
/*   Updated: 2023/07/04 21:08:41 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**g_list_env;

/* sort the environement by ascii */
static int	sort_env_ascii(void)
{
	t_list	**copy;

	copy = malloc(sizeof(t_list));
	if (!copy)
		return (1);
	ft_memset(copy, 0, sizeof(t_list));
	copy = ft_copy_list(copy);
	copy = sort_env(copy);
	print_export(copy);
	free_list(copy);
	return (0);
}

/* add new variable to the environement */
static int	add_var_env(char *stock, t_list *tmp)
{
	char	*copy;
	char	*msg_err;
	(void)tmp;
	
	if (stock[0] == '=')
    {
		err_write("export: `=': not a valid identifier\n", 1);
		free(stock);
        return (1);
    }
	copy = del_equal(stock);
	if (!(is_alphanum(copy) == 0 && is_abc(copy[0]) == 0))
	{
		msg_err = ft_strjoin("export: `", copy);
		if (copy[0] == '-')
		{
			msg_err = ft_strjoin_mod(msg_err,"': invalid option\n", 1);
			err_write(msg_err, 2);
		}
		else if (contain_exclam(copy) == 1)
		{
			msg_err = ft_strjoin_mod(msg_err,"': event not found\n", 1);
			err_write(msg_err, 0);
		}
		else
		{
			msg_err = ft_strjoin_mod(msg_err,"': not a valid identifier\n", 1);
			err_write(msg_err, 1);
		}
		free(msg_err);
		free(copy);
		free(stock);
		return (1);
	}
	if (contain_exclam(stock) == 1)
	{
		msg_err = ft_strjoin("export: `", stock);
		msg_err = ft_strjoin_mod(msg_err,"': event not found\n", 1);
		err_write(msg_err, 0);
		free(msg_err);
		free(copy);
		return (1);
	}
	add_list(g_list_env, stock, 0);
	free(copy);
	return (0);
}

/* modify the value of an environement arg that already exist */
static int	modify_var(char *stock, t_list *tmp)
{
	char	*copy_env;
	char	*copy_token;

	while (*g_list_env)
	{
		copy_env = del_equal((*g_list_env)->content);
		copy_token = del_equal(stock);
		if (ft_strcmp(copy_env, copy_token) == 1)
			(*g_list_env) = (*g_list_env)->next;
		else if (ft_strcmp(copy_env, copy_token) == 0)
		{
			free((*g_list_env)->content);
			(*g_list_env)->content = ft_strdup(stock);
			*g_list_env = tmp;
			free(copy_env);
			free(copy_token);
			return (1);
		}
		free(copy_env);
		free(copy_token);
	}
	return (0);
}

int	ft_export(t_list **list_token)
{
	t_list	*tmp;
	char	*stock;
	char	*copy;
	
	tmp = *g_list_env;
	// remove_empty_tokens(list_token);
	// print_list(list_token);
	if (ft_lstsize(*list_token) == 1)
	{
		if (sort_env_ascii() != 0)
			return (1);
	}
	else
	{
		while (*list_token != NULL)
		{
			(*list_token) = (*list_token)->next;
			if (check_equal((*list_token)->content) == 0)
			{
				stock = ft_strdup((*list_token)->content);
				stock = ft_strjoin_mod(stock, "=", 1);
			}
			else
				stock = ft_strdup((*list_token)->content);
			(*list_token) = (*list_token)->next;
			while (*list_token && (*list_token)->content[0] != '=' && (*list_token)->flag_space == 0)
			{
				if (*list_token && ft_strlen((*list_token)->content) == 0)
					(*list_token) = (*list_token)->next;
				else
				{
					stock = ft_strjoin_mod(stock, (*list_token)->content, 1);
					(*list_token) = (*list_token)->next;
				}
			}
			copy = del_equal(stock);
			if (is_in_env(copy) == 0)
			{
				free(copy);
				add_var_env(stock, tmp);
				return (0);
			}
			else if (modify_var(stock, tmp) == 1)
			{
				free(copy);
				free(stock);
				return (0);
			}
			else
			{
				free(copy);
				free(stock);
			}
			(*list_token) = (*list_token)->next;
		}
	}
	*g_list_env = tmp;
	return (0);
}
