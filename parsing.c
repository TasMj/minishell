/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:50:57 by tmejri            #+#    #+#             */
/*   Updated: 2023/02/20 16:57:23 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*ss;
	int		i;
	int		len_s;

	i = 0;
	len_s = ft_strlen(s);
	ss = (char *)malloc(sizeof(char) * len_s + 1);
	if (ss == 0)
		return (NULL);
	while (s[i])
	{
		ss[i] = s[i];
		i++;
	}
	ss[i] = '\0';
	return (ss);
}

int main(int argc, char **argv)
{
    int i;
    char    **tab;
    
    i = 0;
    tab = malloc(sizeof(char *) * argc);
    while(i < argc)
    {
        tab[i] = ft_strdup(argv[i]);
        i++;
    }

    i = 0;
    while(i < argc)
    {
        printf("%s\n", tab[i]);
        i++;
    }
    return (0);
}

