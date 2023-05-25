/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:09:31 by tas               #+#    #+#             */
/*   Updated: 2023/05/25 15:05:51 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

// echo -n $USER t $fd fd

int	ft_n(char *str)
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

void	set_echo(t_list **list_token, t_echo *e)
{
	if ((*list_token)->next != NULL)
		(*list_token) = (*list_token)->next;
	while (ft_strncmp((*list_token)->content, "-n", 2) == 0
		&& ft_n((*list_token)->content) == 0)
	{
		e->flag = 1;
		if ((*list_token)->next == NULL)
			break ;
		(*list_token) = (*list_token)->next;
	}
	while (*list_token)
	{
		e->to_free = 1;
		e->stockage = ft_strjoin(e->stockage, (*list_token)->content);
		if ((*list_token)->next != NULL && (*list_token)->next->flag_space == 1)
			e->stockage = ft_strjoin(e->stockage, " ");
		(*list_token) = (*list_token)->next;
	}
}

int	ft_echo(t_list **list_token)
{
	t_list	*tmp;
	t_echo	*e;

	e = malloc(sizeof(t_echo));
	ft_memset(e, 0, sizeof(t_echo));
	e->flag = 0;
	e->to_free = 0;
	e->stockage = "";
	tmp = *list_token;
	while ((*list_token) != NULL)
		set_echo(list_token, e);
	if (e->flag != 1)
		printf("%s\n", e->stockage);
	else
		printf("%s", e->stockage);
	if (e->to_free == 1)
		free(e->stockage);
	*list_token = tmp;
	return (0);
}
