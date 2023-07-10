/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:10:29 by tas               #+#    #+#             */
/*   Updated: 2023/07/10 16:42:45 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		g_exit_code = 1;
		perror("pwd error");
	}
}

int	handle_pwd(t_cmd *cmd)
{
	char	*msg_err;
	int		i;

	i = 1;
	if (ft_lstsize(*cmd->cmd) > 1 && (*cmd->cmd)->next->content[0] == '-')
	{
		while ((*cmd->cmd)->next->content[i] == '-')
				i++;
		if (ft_strlen((*cmd->cmd)->next->content) == i
			&& (*cmd->cmd)->next->content[i] == '\0')
			return (ft_pwd(), 1);
		msg_err = ft_strjoin("pwd: ", (*cmd->cmd)->next->content);
		msg_err = ft_strjoin_mod(msg_err, ": invalid option\n", 1);
		msg_err = ft_strjoin_mod(msg_err, "pwd: usage: pwd [-LP]\n", 1);
		err_write(msg_err, 2);
		return (free(msg_err), 1);
	}
	ft_pwd();
	return (0);
}
