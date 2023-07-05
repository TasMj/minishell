/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:33:10 by tmejri            #+#    #+#             */
/*   Updated: 2023/07/05 15:07:44 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void    free_list_token_content(t_list **list_token)
{
    t_list *tmp;

    if (!list_token)
        return ;
    tmp = (*list_token);
    while (tmp)
    {
		// printf("free g_list %p\n", tmp->content);
		if (tmp->content)
		{
			if (tmp->content != NULL)
			{
				// printf("1 : %s\n", tmp->content);
				free(tmp->content);
			}
		}
        tmp = tmp->next;
    }
}

void	free_list(t_list **list)
{
	t_list	*to_free;
	t_list	*iter;

	if (*list)
	{
		iter = *list;
		while (iter)
		{
			to_free = iter;
			iter = iter->next;
			free(to_free);
		}
		*list = NULL;
	}
	free(list);
}

void	free_all(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

void	free_end(t_minishell *data)
{
	free_list_token_content(data->token);
    free_list(data->token);
    free(data->	input);
	free_list_token_content(g_list_env);
	free_list(g_list_env);
}

int	free_and_ret(char *s1, char *s2, int ret)
{
	free(s1);
	free(s2);
	return (ret);
}