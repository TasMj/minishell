/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:57:06 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/21 22:19:42 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Retourne le nombre de token avant l'operateur
int	cmd_size(t_list *token)
{
	int	count;
	
	count = 0;
	while (token && token->type != PIPE)
	{
		count++;
		token = token->next;
	}
	return (count);
}

// Retourne la commande avec les args jusquau premier operateur
t_list	**get_cmd(t_list *tok)
{
	t_list	**lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	*lst = NULL;
	while (tok && tok->type != PIPE)
	{
		add_list(lst, tok->content, tok->flag_space);
		tok = tok->next;
	}
	get_type(lst);
	return (lst);
}

// Setup chaque commande dans une struct cmd
void	setup_cmd(t_exec *data)
{
	int	i;
	t_list	*token;
	t_path	p;

	token = *(data->token);
	data->cmd = malloc(sizeof(t_cmd) * nb_cmd(token));
	ft_memset(&p, 0, sizeof(t_path));
	i = 0;
	while (token)
	{
		data->cmd[i].id = i;
		data->cmd[i].cmd = get_cmd(token);
		data->cmd[i].path = find_path(data->env, (*data->cmd[i].cmd)->content, p);
		set_fd(&(data->cmd[i]), data);
		while (token->type != PIPE && token->next)
			token = token->next;
		token = token->next;
		i++;
	}
}
