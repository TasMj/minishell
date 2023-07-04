/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:21:12 by jthuysba          #+#    #+#             */
/*   Updated: 2023/07/04 20:07:52 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_lst_type(t_list **list_token, t_list *elem)
{
	t_list	*to_add;

	to_add = ft_lstnew(elem->content, elem->flag_space);
	to_add->type = elem->type;
	to_add->quote_trace = elem->quote_trace;
	ft_lstadd_back(list_token, to_add);
}

/* On clone les token jusqua un pipe ou la fin
-> {cat < file} */
static t_list    **clone_to_pipe(t_list *token)
{
    t_list    **lst;
    t_list    *elem;
  
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
	/* Si la commande est un path */
	if (!cmd->cmd)
		return (0);
	if (cmd->cmd && has_slash(cmd) == 1)
	{
		if (access((*cmd->cmd)->content, F_OK) == -1)
		{
			msg_err = ft_strjoin((*cmd->cmd)->content, ": No such file or directory\n");
			err_write(msg_err, 2);
			cmd->data->code_err = 127;
			free(msg_err);
			return (1);
		}
		else if (access((*cmd->cmd)->content, X_OK) == -1)
		{
			(void)msg_err;
			put_str_err("minishell: ");
			put_str_err((*cmd->cmd)->content);
			put_str_err(": Permission denied\n");
			cmd->data->code_err = 126;
			return (1);
		}
		else if (is_dir((*cmd->cmd)->content) == 1)
		{
			msg_err = ft_strjoin((*cmd->cmd)->content, ": Is a directory\n");
			err_write(msg_err, 2);
			cmd->data->code_err = 126;
			free(msg_err);
			return (1);
		}
		return (0);
	}
	/* Sinon ex : ls -a, cat ou jules */
	cmd->tab = lst_to_tab(g_list_env);
	if (is_in_env("PATH") == 1)
		cmd->path = find_path(cmd->tab, (*cmd->cmd)->content);
	if (!cmd->path && is_builtin(cmd) == 0)
	{
		put_str_err("minishell: ");
		put_str_err((*cmd->cmd)->content);
		put_str_err(": command not found\n");
		// msg_err = ft_strjoin((*cmd->cmd)->content, ": command not found\n");
		// err_write(msg_err, 2);
		if (cmd->id == cmd->data->x->nb_cmd - 1)
			cmd->data->code_err = 127;
		return (free_tab(cmd->tab), 0);
	}
	free_tab(cmd->tab);
	return (0);
}

/* Init tous les param de chaque cmd */
static int	fill_cmd(t_cmd *cmd)
{
	/* On attribue a cmd la commande sans les op */
	cmd->cmd = get_cmd(*(cmd->token));
	if (check_cmd(cmd) != 0)
		return (1);
	if (cmd->cmd)
		cmd->tab = lst_to_tab(cmd->cmd);
	cmd->pid = 0;
	handle_redir(cmd, *(cmd->token));
	// free(cmd->tab);
	
	return (0);
}

/* Setup les commandes en t_cmd */
int	prep_cmd(t_minishell *data)
{
	t_list	*elem;
	int	i;
	int	ret;

	/* On compte les commandes en fonction des pipes
	-> 1 pipe => 2 commandes */
	data->x->nb_cmd = nb_cmd(*data->token);
	if (data->x->nb_cmd == 0)
		return (2);
	data->x->cmd = malloc(sizeof(t_cmd) * data->x->nb_cmd);
	if (!data->x->cmd)
		return (1);
	set_to_zero(data->x);
	elem = *(data->token);
	i = 0;
	while (elem)
	{
		/* On initialise tous les param de chaque cmd */
		data->x->cmd[i].data = data;
		data->x->cmd[i].id = i;
		data->x->cmd[i].token = clone_to_pipe(elem);
		ret = fill_cmd(&(data->x->cmd[i]));
		// if (data->x->cmd[i].cmd)
		// 	print_list(data->x->cmd[i].cmd);
		// else
		// 	printf("NULL\n");
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
