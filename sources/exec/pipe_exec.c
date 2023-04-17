/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:08:40 by jthuysba          #+#    #+#             */
/*   Updated: 2023/04/17 16:04:21 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// int	check_pipes(t_list **tokens)
// {
// 	t_list	*token;
	
// 	token = *tokens;
// 	while (token)
// 	{
// 		if (token->type == 5)
// 			return (1);
// 		token = token->next;
// 	}
// 	return (0);
// }

// //Retourne le nombre de token avant l'operateur
// int	cmd_size(t_list **tokens)
// {
// 	t_list	*token;
// 	int	count;
	
// 	token = *tokens;
// 	count = 0;
// 	while (token && token->type == 0)
// 	{
// 		count++;
// 		token = token->next;
// 	}
// 	return (count);
// }

// char	**get_cmd1(t_list **tokens)
// {
// 	char		**cmd;
// 	t_list	*token;
// 	int		i;

// 	cmd = malloc(sizeof(char *) * (cmd_size(tokens) + 1));
// 	token = *tokens;
// 	i = 0;
// 	while (token && token->type == 0)
// 	{
// 		cmd[i] = ft_strdup_size(token->content, ft_strlen(token->content));
// 		i++;
// 		token = token->next;
// 	}
// 	cmd[i] = 0;
// 	return (cmd);
// }

// void	get_cmds(t_list **tokens, t_pipe *p)
// {
// 	t_list	*token;
// 	int		i;
	
// 	p->cmd1 = malloc(sizeof(char *) * (cmd_size(tokens) + 1));
// 	token = *tokens;
// 	i = 0;
// 	while (token && token->type == 0)
// 	{
// 		cmd[i] = ft_strdup_size(token->content, ft_strlen(token->content));
// 		i++;
// 		token = token->next;
// 	}
// 	cmd[i] = 0;
// 	return (cmd);
// }

// int	pipe_exec(t_list **tokens, char **env)
// {
// 	t_pipe	p;
	
// 	// p.cmd1 = get_cmd1(tokens);
// 	// p.cmd2 = get_cmd2(tokens);
// 	get_cmds(tokens, &p);
	
// 	if (pipe(p.fd) == -1)	//Creation pipe	
// 		return (1);
		
// 	p.pid1 = fork(); 		//Creation child process 1 -> cmd1
// 	if (p.pid1 < 0)
// 		return (2);

// 	if (p.pid1 == 0)		//Si child process (cmd1)
// 	{
// 		dup2(p.fd[1], STDOUT_FILENO);
// 		close(p.fd[0]);
// 		close(p.fd[1]);
// 		execve(find_path(env, p.cmd1[0], p.path), p.cmd1, env);
// 	}

// 	p.pid2 = fork();
// 	if (p.pid2 < 0)
// 		return (3);

// 	if (p.pid2 == 0)
// 	{
// 		dup2(STDIN_FILENO, p.fd[0]);
// 		close(p.fd[1]);
// 		close(p.fd[0]);
// 		execve(find_path(env, p.cmd2[0], p.path), p.cmd2, env);
// 	}
	
// 	waitpid(p.pid1, NULL, 0);

// 	free_tab(p.cmd1);
// 	return (0);
// }