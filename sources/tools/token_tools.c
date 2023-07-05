/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:04:12 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/05 21:04:41 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_empty_token(t_list **list)
{
	char		*str;
	t_list		*to_free;
	t_list		*temp;

	while (*list && !((*list)->content)[0])
	{
		to_free = *list;
		*list = (*list)->next;
		free(to_free->content);
		free(to_free);
	}
	temp = *list;
	while (temp && temp->next)
	{
		str = temp->next->content;
		if (!str[0])
		{
			to_free = temp->next;
			temp->next = temp->next->next;
			free(to_free->content);
			free(to_free);
		}
		temp = temp->next;
	}
}

void	remove_empty_tokens(t_list **list)
{
	t_list	*tmp;
	int		prev_flag;
	int		a;

	a = 0;
	tmp = *list;
	while (*list)
	{
		if (a == 1 && (*list)->flag_space == 0)
		{
			(*list)->flag_space = prev_flag;
			a = 0;
		}
		if (ft_strlen((*list)->content) == 0)
		{
			a = 1;
			prev_flag = (*list)->flag_space;
		}
		(*list) = (*list)->next;
	}
	*list = tmp;
	free_empty_token(list);
}

void	add_space(t_minishell *data)
{
	t_list	*tmp;
	t_list	*prev;
	char	*to_add;

	tmp = *data->token;
	to_add = NULL;
	while (*data->token)
	{
		if ((*data->token)->flag_space == 1
			&& ft_strlen((*data->token)->content) != 0)
		{
			if (ft_strlen(prev->content) == 0)
			{
				to_add = ft_strdup(" ");
				to_add = ft_strjoin_mod(to_add, (*data->token)->content, 1);
				free((*data->token)->content);
				(*data->token)->content = ft_strdup(to_add);
				free(to_add);
			}
		}
		prev = *data->token;
		(*data->token) = (*data->token)->next;
	}
	*data->token = tmp;
}
