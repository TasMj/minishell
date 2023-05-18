/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:06:03 by jthuysba          #+#    #+#             */
/*   Updated: 2023/05/18 16:07:16 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_word(char *tok)
{
	if (check_redir_in(tok[0]) == 1 || check_redir_out(tok[0]) == 1 ||
		check_append(tok) == 1 || check_heredoc(tok) == 1)
		return (0);
	return (1);
}

int	size_to_op(char **cmd)
{
	int	i;

	i = 0;
	while (is_word(cmd[i]) == 1)
		i++;
	return (i);
}

char	**get_cut_cmd(char **cmd)
{
	char	**ex_cmd;
	int		i;

	ex_cmd = malloc(sizeof(char *) * size_to_op(cmd) + 1);
	i = 0;
	while (is_word(cmd[i]) == 1)
	{
		ex_cmd[i] = ft_strdup_size(cmd[i], ft_strlen(cmd[i]));
		i++;
	}
	ex_cmd[i] = 0;
	return (ex_cmd);
}
