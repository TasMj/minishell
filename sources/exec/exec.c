/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:57:13 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/30 01:18:40 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (ft_strlen((*cmd->cmd)->content) == 2 && ft_strncmp((*cmd->cmd)->content, "cd", 2) == 0)
		return (1);
	else if (ft_strlen((*cmd->cmd)->content) == 4 && ft_strncmp((*cmd->cmd)->content, "echo", 4) == 0)
		return (1);
	else if (ft_strlen((*cmd->cmd)->content) == 3 && ft_strncmp((*cmd->cmd)->content, "env", 3) == 0)
		return (1);
	else if (ft_strlen((*cmd->cmd)->content) == 4 && ft_strncmp((*cmd->cmd)->content, "exit", 4) == 0)
		return (1);
	else if (ft_strlen((*cmd->cmd)->content) == 6 && ft_strncmp((*cmd->cmd)->content, "export", 6) == 0)
		return (1);
	else if (ft_strlen((*cmd->cmd)->content) == 3 && ft_strncmp((*cmd->cmd)->content, "pwd", 3) == 0)
		return (1);
	else if (ft_strlen((*cmd->cmd)->content) == 5 && ft_strncmp((*cmd->cmd)->content, "unset", 5) == 0)
		return (1);
	return (0);
}

/* On lance un process pour chaque commande */
static int	launch_process(t_cmd *cmd, t_minishell *data)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (1);
	if (cmd->pid == 0)
	{
		dup_pipe(cmd, data->x);
		if (open_n_dup(cmd, data->x) != 0)
		{
			// destroy_exec(data->x);
			ft_exit(data);
		}
		if (cmd->cmd)
			exec_it(cmd , data);
		else
			ft_exit(data);
	}
	return (0);
}

int	wait_child(t_xek *x)
{
	int	i;
	int	ret;

	close_all(x);
	i = 0;
	ret = 0;
	while (i < x->nb_cmd)
	{
		if (!x->cmd[i].cmd|| is_builtin(&x->cmd[i]) == 0)
		{
			waitpid(x->cmd[i].pid, &ret, WUNTRACED);
			if (x->cmd[i].id == x->nb_cmd - 1)
			{
				if (WIFEXITED(ret))
					x->cmd->data->code_err = WEXITSTATUS(ret);
				else
				{
					x->cmd->data->code_err = WTERMSIG(ret) + 128;
					if (x->cmd->data->code_err == 139)
						err_write("Segmentation fault error\n", x->cmd->data->code_err);
				}
			}
		}
		i++;
	}
	return (0);
}

/* Execute les commandes */
int	go_exec(t_xek *x, t_minishell *data)
{
	int	i;
	
	/* On lance un process pour chaque commande */
	i = 0;
	signal_ignore();
	while (i < x->nb_cmd)
	{
		if (!x->cmd[i].cmd || is_builtin(&(x->cmd[i])) == 0)
			launch_process(&(x->cmd[i]), data);
		else if (is_builtin(&(x->cmd[i])) == 1)
			if (handle_builtin(&(x->cmd[i]), data) != 0)
				return (wait_child(x), 1);
		i++;
	}
	wait_child(x);
	set_signal();
	return (0);
}

int	open_n_leave(t_list	*token)
{
	int	fd;

	while (token)
	{
		if (token->type == STDOUT)
		{
			fd = open(token->next->content, O_CREAT | O_TRUNC | O_RDWR, 0666);
			close(fd);
		}
		else if (token->type == APPEND)
		{
			fd = open(token->next->content, O_CREAT | O_APPEND | O_RDWR, 0666);
			close(fd);
		}
		else if (token->type == STDIN)
		{
			fd = open(token->content, O_RDONLY);
			if (fd < 0)
			{
				put_str_err("minishell: ");
				put_str_err(token->next->content);
				put_str_err(": No such file or directory\n");
				// if (!(x->nb_cmd > 1 && cmd->id == 0))
				// 	cmd->data->code_err = 1;
				return (1);
			}
		}
		token = token->next;
	}
	return (0);
}

/* Execute les tokens
-> cat < file | wc -l > file2 */
int	we_exec(t_minishell *data)
{
	int	ret;

	data->x = malloc(sizeof(t_xek));
	ft_memset(data->x, 0, sizeof(t_xek));
	if (ft_strcmp((*data->token)->content, "export") == 0)
		remove_empty_tokens(data->token);
	ret = prep_cmd(data);
	if (ret == 1)
		return (destroy_exec(data->x), 1);
	else if (ret == 2)
	{
		open_n_leave(*data->token);
		destroy_exec(data->x);
		return (0);
	}
	open_pipes(data);
	exec_heredoc(data);
	if (go_exec(data->x, data) != 0)
	{
		data->code_err = 1;
		return (destroy_exec(data->x), 1);
	}
	destroy_exec(data->x);
	return (0);
}
