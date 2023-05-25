/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:43:10 by tmejri            #+#    #+#             */
/*   Updated: 2023/05/25 16:46:59 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

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
	if (s->stock)
		free(s->stock);
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

void	free_heredoc(t_heredoc *h)
{
	if (h->delimiteur)
		free(h->delimiteur);
	if (h->cmd)
		free(h->cmd);
	if (h->path_cmd)
		free(h->path_cmd);
}
