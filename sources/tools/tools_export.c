/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:49:28 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/05 21:53:55 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_add_env(char *msg_err, char *stock, char *copy)
{
	msg_err = ft_strjoin("export: `", copy);
	if (copy[0] == '-')
	{
		msg_err = ft_strjoin_mod(msg_err, "': invalid option\n", 1);
		err_write(msg_err, 2);
	}
	else if (contain_exclam(copy) == 1)
	{
		msg_err = ft_strjoin_mod(msg_err, "': event not found\n", 1);
		err_write(msg_err, 0);
	}
	else
	{
		msg_err = ft_strjoin_mod(msg_err, "': not a valid identifier\n", 1);
		err_write(msg_err, 1);
	}
	free(msg_err);
	free(copy);
	free(stock);
	return (1);
}

void	err_exclam(char *msg_err, char *stock, char *copy)
{
	msg_err = ft_strjoin("export: `", stock);
	msg_err = ft_strjoin_mod(msg_err, "': event not found\n", 1);
	err_write(msg_err, 0);
	free(msg_err);
	free(copy);
}

int	add_modif(char *copy, char *stock, t_list *tmp)
{
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
	return (1);
}

char	*set_stock(char *str, char *stock)
{
	if (check_equal(str) == 0)
	{
		stock = ft_strdup(str);
		stock = ft_strjoin_mod(stock, "=", 1);
	}
	else
		stock = ft_strdup(str);
	return (stock);
}
