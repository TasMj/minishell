/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:57:06 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/18 15:41:26 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// Set le type de chaque commande
void	set_type(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
	{
		if (ft_strncmp(cmd->cmd[i], "<", 1) == 0)
			cmd->type = STDIN;
		else if (ft_strncmp(cmd->cmd[i], ">", 1) == 0)
			cmd->type = STDOUT;
		if (ft_strncmp(cmd->cmd[i], "<<", 2) == 0)
			cmd->type = HEREDOC;
		else if (ft_strncmp(cmd->cmd[i], ">>", 2) == 0)
			cmd->type = APPEND;
		if (cmd->type != 0)
			return ;
		i++;
	}
}

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
char	**get_cmd(t_list *token)
{
	char		**cmd;
	int		i;

	cmd = malloc(sizeof(char *) * (cmd_size(token) + 1));
	i = 0;
	while (token && token->type != PIPE)
	{
		cmd[i] = ft_strdup_size(token->content, ft_strlen(token->content));
		i++;
		token = token->next;
	}
	cmd[i] = 0;
	return (cmd);
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
		data->cmd[i].path = find_path(data->env, data->cmd[i].cmd[0], p);
		data->cmd[i].type = 0;
		set_type(&(data->cmd[i]));
		set_fd(&(data->cmd[i]), data);
		while (token->type != PIPE && token->next)
			token = token->next;
		token = token->next;
		i++;
	}
}
