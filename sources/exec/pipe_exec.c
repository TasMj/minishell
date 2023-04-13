/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:08:40 by jthuysba          #+#    #+#             */
/*   Updated: 2023/04/13 17:46:42 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipes(t_list **tokens)
{
	t_list	*token;
	
	token = *tokens;
	while (token)
	{
		if (token->type == 5)
			return (1);
		token = token->next;
	}
	return (0);
}

int	cmd_size(t_list **tokens)
{
	t_list	*token;
	int	count;
	
	token = *tokens;
	count = 0;
	while (token && token->type == 0)
	{
		count++;
		token = token->next;
	}
	return (count);
}

// char	**get_cmd1(t_list **tokens)
// {
// 	char	**cmd;
	
// 	cmd = malloc(sizeof(char *) * (cmd_size(tokens) + 1));
// }

int	pipe_exec(t_list **tokens, char **env)
{
	t_pipe	p;
	
	// p.cmd1 = get_cmd1(tokens);
	printf("%d\n", cmd_size(tokens));
	(void) p;
	(void) env;
	// if (pipe(p.fd) == -1)	//Creation pipe	
	// 	return (1);
		
	// p.pid1 = fork(); 		//Creation child process 1 -> cmd1
	// if (p.pid1 < 0)
	// 	return (2);

	// if (p.pid1 == 0)		//Si child process (cmd1)
	// {
	// 	execve(, , env);
	// }
	return (0);
}