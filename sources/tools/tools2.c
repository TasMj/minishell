/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:24:17 by tmejri            #+#    #+#             */
/*   Updated: 2023/05/26 16:16:01 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

int	ft_strcmp(char *s1, char *s2)
{
	char	*ss1;
	char	*ss2;
	int		i;

	ss1 = s1;
	ss2 = s2;
	i = 0;
	if (ft_strlen(ss1) != ft_strlen(ss2))
		return (1);
	else
	{
		while (i < ft_strlen(ss1))
		{
			if (ss1[i] == ss2[i])
				i++;
			else
				return (1);
		}
	}
	return (0);
}
