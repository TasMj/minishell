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

int	exec_it(t_cmd *cmd, t_minishell *data)
{
	signal_default();
	if (!cmd->path && is_builtin(cmd) == 0 && has_slash(cmd) == 0)
		ft_exit(data);
	cmd->tab_env = lst_to_tab(g_list_env);
	if (has_slash(cmd) == 1)
	{
		if (execve((*cmd->cmd)->content, cmd->tab, cmd->tab_env) != 0)
			return (1);
	}
	else
	{
		if (execve(cmd->path, cmd->tab, cmd->tab_env) != 0)
			return (1);
	}
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
			ft_exit(data);
		if (cmd->cmd)
			exec_it(cmd, data);
		else
			ft_exit(data);
	}
	return (0);
}

int	wait_child(t_xek *x)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	while (++i < x->nb_cmd)
	{
		if (!x->cmd[i].cmd || is_builtin(&x->cmd[i]) == 0)
		{
			waitpid(x->cmd[i].pid, &ret, WUNTRACED);
			set_signal();
			if (x->cmd[i].id == x->nb_cmd - 1)
			{
				if (WIFEXITED(ret))
					g_exit_code = WEXITSTATUS(ret);
				else if (WIFSIGNALED(ret))
					handle_term_sig(ret);
			}
		}
	}
	return (0);
}

/* Execute les commandes */
int	go_exec(t_xek *x, t_minishell *data)
{
	int	i;

	i = 0;
	while (i < x->nb_cmd)
	{
		signal_ignore();
		if (!x->cmd[i].cmd || is_builtin(&(x->cmd[i])) == 0)
			launch_process(&(x->cmd[i]), data);
		else if (is_builtin(&(x->cmd[i])) == 1)
			if (handle_builtin(&(x->cmd[i]), data) != 0)
				return (close_all(x), wait_child(x), 1);
		i++;
	}
	close_all(x);
	wait_child(x);
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
		g_exit_code = 1;
		return (destroy_exec(data->x), 1);
	}
	destroy_exec(data->x);
	return (0);
}
