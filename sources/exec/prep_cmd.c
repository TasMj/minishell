/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:21:12 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/10 16:44:04 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* On clone les token jusqua un pipe ou la fin
-> {cat < file} */
static t_list	**clone_to_pipe(t_list *token)
{
	t_list		**lst;
	t_list		*elem;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	*lst = NULL;
	elem = token;
	while (elem && elem->type != PIPE)
	{
		add_lst_type(lst, elem);
		elem = elem->next;
	}
	return (lst);
}

/* Retourne la commande brut sans les redir
-> {cat} {wc -l}, etc) */
static t_list	**get_cmd(t_list *token)
{
	t_list	**lst;
	t_list	*elem;

	elem = token;
	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	*lst = NULL;
	while (elem)
	{
		if (elem->type != WORD)
		{
			if (elem->next)
				elem = elem->next;
			else
				return (lst);
		}
		else if (elem->type == WORD)
			add_list(lst, elem->content, elem->flag_space);
		elem = elem->next;
	}
	if (*lst == NULL)
		return (free(lst), NULL);
	return (lst);
}

/* Verifie si la commande est valide 
ex : ls -> OK, jules -> not found */
static int	check_cmd(t_cmd *cmd)
{
	char	*msg_err;

	msg_err = 0;
	if (!cmd->cmd)
		return (0);
	if (cmd->cmd && (has_slash(cmd) == 1 || (is_in_env("PATH") == 0 && is_builtin(cmd) == 0)))
		return (cmd_access(cmd, msg_err));
	cmd->tab = lst_to_tab(g_list_env);
	if (is_in_env("PATH") == 1)
		cmd->path = find_path(cmd->tab, (*cmd->cmd)->content);
	if (!cmd->path && is_builtin(cmd) == 0)
	{
		put_str_err("minishell: ");
		put_str_err((*cmd->cmd)->content);
		put_str_err(": command not found\n");
		if (cmd->id == cmd->data->x->nb_cmd - 1)
			g_exit_code = 127;
		return (free_tab(cmd->tab), 0);
	}
	free_tab(cmd->tab);
	return (0);
}

/* Init tous les param de chaque cmd */
static int	fill_cmd(t_cmd *cmd, t_list *elem)
{
	cmd->data = singleton_minishell();
	cmd->token = clone_to_pipe(elem);
	cmd->cmd = get_cmd(*(cmd->token));
	if (check_cmd(cmd) != 0)
		return (1);
	if (cmd->cmd)
		cmd->tab = lst_to_tab(cmd->cmd);
	cmd->pid = 0;
	handle_redir(cmd, *(cmd->token));
	return (0);
}

/* Setup les commandes en t_cmd */
int	prep_cmd(t_minishell *data)
{
	t_list	*elem;
	int		i;
	int		ret;

	data->x->nb_cmd = nb_cmd(*data->token);
	if (data->x->nb_cmd == 0)
		return (2);
	if (set_prep_tools(data) != 0)
		return (1);
	elem = *(data->token);
	i = 0;
	while (elem)
	{
		data->x->cmd[i].id = i;
		ret = fill_cmd(&(data->x->cmd[i]), elem);
		if (ret != 0)
			return (ret);
		while (elem && elem->type != PIPE)
			elem = elem->next;
		if (elem && elem->type == PIPE)
			elem = elem->next;
		i++;
	}
	return (0);
}
