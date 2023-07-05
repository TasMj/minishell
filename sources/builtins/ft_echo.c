/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:09:31 by tas               #+#    #+#             */
/*   Updated: 2023/07/05 22:00:41 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static	int	handle_token(t_list **list_token, t_echo *e)
{
	while ((*list_token)->next && ft_strlen((*list_token)->next->content) >= 2
		&& ft_strncmp((*list_token)->next->content, "-n", 2) == 0
		&& (ft_n((*list_token)->next->content) == 0))
			(*list_token) = (*list_token)->next;
	e->flag = 1;
	if ((*list_token)->next == NULL)
		return (1);
	(*list_token) = (*list_token)->next;
	return (0);
}

static	int	handle_content(t_list **list_token, t_echo *e)
{
	while (*list_token)
	{
		e->to_free = 1;
		e->stockage = ft_strdup((*list_token)->content);
		if ((*list_token)->next != NULL)
			(*list_token) = (*list_token)->next;
		else
			return (1);
		while (*list_token)
		{
			e->stockage = ft_strjoin_mod(e->stockage, " ", 1);
			e->stockage = ft_strjoin_mod(e->stockage, \
			(*list_token)->content, 1);
			(*list_token) = (*list_token)->next;
		}
	}
	return (0);
}

static	int	set_echo(t_list **list_token, t_echo *e)
{
	(*list_token) = (*list_token)->next;
	if (ft_strlen((*list_token)->content) >= 2
		&& ft_strncmp((*list_token)->content, "-n", 2) == 0
		&& (ft_n((*list_token)->content) == 0))
	{
		if (handle_token(list_token, e) == 1)
			return (1);
	}
	if (handle_content(list_token, e) == 1)
		return (1);
	return (0);
}

int	ft_echo(t_list **list_token)
{
	t_list	*tmp;
	t_echo	*e;

	e = malloc(sizeof(t_echo));
	if (!e)
		return (1);
	ft_memset(e, 0, sizeof(t_echo));
	// e->stockage = "";
	tmp = *list_token;
	while ((*list_token) != NULL)
	{
		if (ft_strncmp((*list_token)->content, "echo", 4) == 0
			&& (*list_token)->next != NULL)
			set_echo(list_token, e);
		else
			(*list_token) = (*list_token)->next;
	}
	if (e->flag != 1 && e->stockage != NULL)
		printf("%s\n", e->stockage);
	else if (e->flag != 0 && e->stockage != NULL)
		printf("%s", e->stockage);
	if (e->to_free == 1)
		free(e->stockage);
	*list_token = tmp;
	return (free_and_ret((char *)e, NULL, 0));
}
