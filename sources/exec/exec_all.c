// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   exec_all.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/04/17 14:12:39 by jthuysba          #+#    #+#             */
// /*   Updated: 2023/05/09 14:09:16 by jthuysba         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// //Retourne le token avant elem
// t_list	*lst_previous(t_list *token, t_list *elem)
// {
// 	if (!token->next)
// 		return (NULL);
// 	while (token->next != elem && token)
// 		token = token->next;
// 	return (token);
// }

// //Retourne le nombre de token avant l'operateur
// int	cmd_size(t_list *token)
// {
// 	int	count;
	
// 	count = 0;
// 	while (token && token->type == WORD)
// 	{
// 		count++;
// 		token = token->next;
// 	}
// 	return (count);
// }

// int	last_cmd(t_list *token)
// {
// 	while (token)
// 	{
// 		if (token->type != WORD)
// 			return (0);
// 		token = token->next;
// 	}
// 	return (1);
// }

// int	exec_cmd(t_list *token, char **env, int cmd_nb, t_exec ex)
// {
// 	(void) cmd_nb;
// 	(void) ex;
// 	char	**cmd;
// 	int	pid;
// 	t_path	p;
	
// 	cmd = get_cmd(token);
// 	pid = fork();
// 	if (pid < 0)
// 		return (1);
// 	if (pid == 0)
// 	{
// 		// if (cmd_nb == 0)									//Si premiere cmd
// 		// {
// 		// 	dup2(ex.fd[0][1], STDOUT_FILENO);
// 		// 	close_all(ex);
// 		// }
// 		// else if (cmd_nb == ex.pipes_nb)	//Si derniere cmd
// 		// {
// 		// 	dup2(ex.fd[ex.pipes_nb - 1][0], STDIN_FILENO);
// 		// 	close_all(ex);
// 		// }
// 		// else
// 		// {
// 		// 	dup2(ex.fd[cmd_nb - 1][0], STDIN_FILENO);
// 		// 	dup2(ex.fd[cmd_nb][1], STDOUT_FILENO);
// 		// 	close_all(ex);
// 		// }
// 		execve(find_path(env, cmd[0], p), cmd, env);
// 	}
// 	waitpid(pid, NULL, 0);
// 	return (0);
// }

// void	exec(t_list *token, char **env, t_exec ex)
// {
// 	int		cmd_nb;
	
// 	cmd_nb = 0;
	
// 	while (token)
// 	{
// 		// if (last_cmd(token))
// 		// {
// 		// 	exec_cmd(token, env, cmd_nb, ex);
// 		// 	return ;
// 		// }
		
// 		exec_cmd(token, env, cmd_nb, ex);
// 		cmd_nb++;
		
// 		while (token->type != PIPE && token)
// 			token = token->next;
// 		if (token->next)
// 			token = token->next;
// 	}
// }

// // int   exec_all(t_list *token, char **env)
// // {
// // 	(void) env;
// // 	t_exec	ex;
// // 	int		i;

// // 	i = 0;
// // 	ex.first = token;
// // 	ex.pipes_nb = count_pipes(token);
// // 	ex.fd = malloc(sizeof(int *) * count_pipes(token));
// // 	while (i < count_pipes(token))
// // 	{
// // 		ex.fd[i] = malloc(sizeof(int) * 2);
// // 		pipe(ex.fd[i]);
// // 		// printf("i = %d\n", i);
// // 		i++;
// // 	}
// // 	// printf("pipes_nb = %d\n", ex.pipes_nb);
// // 	exec(token, env, ex);
// // 	return (0);
// // }