/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:33:10 by tmejri            #+#    #+#             */
/*   Updated: 2023/05/22 00:12:07 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	free_list(t_list **list)
{
	t_list	*to_free;
	t_list	*iter;

	iter = *list;
	while (iter)
	{
		to_free = iter;
		iter = iter->next;
		free(to_free);
	}
	*list = NULL;
	free(list);
}

void	free_all(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

void	free_substitution(t_substitution *s)
{
	if (s->var_substitute)
		free(s->var_substitute);
	if (s->keep_var)
		free(s->keep_var);
	if (s->keep_var2)
		free(s->keep_var2);
	if (s->new_content)
		free(s->new_content);
	if (s->without_dollar)
		free(s->without_dollar);
	if (s->stockage)
		free(s->stockage);
}

void	free_data(t_data *data)
{
	if (data->cmd)
		free(data->cmd);
	if (data->path_cmd)
		free(data->path_cmd);
	if (data->token_cmd)
		free_tab(data->token_cmd);
}
