/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:09:31 by tas               #+#    #+#             */
/*   Updated: 2023/06/23 04:46:02 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//echo cat<<EOF cat << EOF

/* check if flag n */
static int	ft_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i + 1] && str[i] == '-' && str[i + 1] == 'n')
	{
		i += 2;
		while (str[i])
		{
			if (str[i] != 'n')
				return (1);
			i++;
		}
	}
	return (0);
}

static int	set_echo(t_list **list_token, t_echo *e)
{
	(*list_token) = (*list_token)->next;
	if (ft_strlen((*list_token)->content) >= 2
		&& ft_strncmp((*list_token)->content, "-n", 2) == 0
		&& (ft_n((*list_token)->content) == 0))
	{
		while ((*list_token)->next && ft_strlen((*list_token)->next->content) >= 2
			&& ft_strncmp((*list_token)->next->content, "-n", 2) == 0
			&& (ft_n((*list_token)->next->content) == 0))
			(*list_token) = (*list_token)->next;
		e->flag = 1;
		if ((*list_token)->next == NULL)
			return (0);
		(*list_token) = (*list_token)->next;
	}
	while (*list_token)
	{
		e->to_free = 1;
		e->stockage = ft_strjoin(e->stockage, (*list_token)->content);
		if ((*list_token)->next != NULL)
			(*list_token) = (*list_token)->next;
		else
			return (0);
		while (*list_token)
		{
			e->stockage = ft_strjoin_mod(e->stockage, " ", 1);
			e->stockage = ft_strjoin_mod(e->stockage, (*list_token)->content, 1);
			(*list_token) = (*list_token)->next;
		}
	}
	return (0);
}

int	ft_echo(t_list **list_token)
{
	t_list	*tmp;
	t_echo	*e;

	e = malloc(sizeof(t_echo));
	ft_memset(e, 0, sizeof(t_echo));
	e->stockage = "";
	tmp = *list_token;
	while ((*list_token) != NULL)
	{
		if (ft_strncmp((*list_token)->content, "echo", 4) == 0
			&& (*list_token)->next != NULL)
			set_echo(list_token, e);
		else
			(*list_token) = (*list_token)->next;
	}
	if (e->flag != 1)
		printf("%s\n", e->stockage);
	else
		printf("%s", e->stockage);
	if (e->to_free == 1)
		free(e->stockage);
	*list_token = tmp;
	free(e);
	return (0);
}
