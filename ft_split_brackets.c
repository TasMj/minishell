/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_brackets.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:46:41 by tmejri            #+#    #+#             */
/*   Updated: 2023/02/22 17:27:49 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	nb_word_bracket(const char *s, char c)
{
    size_t compteur;
    
	return (compteur);
}

static char	*ft_copy(char *dest, char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int check_bracket(char *str)
{
    int i;
    int flag_quoat;
    
    i = 0;
    flag_quoat = 0;
    while (str[i] && flag_quoat < 3)
    {
        if (str[i] == 34)
            flag_quoat++;
        i++;
    }
    if (flag_quoat == 2)
        return (1);
    return (0);
}

char	**ft_split_bracket(char *s, char c)
{
	char	**s_split;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	s_split = (char **)malloc(sizeof(char *) * (nb_word_bracket(s, c) + 1));
	while (s[i])
	{
		if (s[i] == c)
        {
            if (check_bracket(s) == 1)
            {
                while (s[i] != c)
                    i++;
            }
            i++;
        }
		else
		{
			k = 0;
			while (s[i + k] != c && s[i + k] != '\0')
				k++;
			s_split[j] = (char *)malloc(sizeof(char) * (k + 1));
			// if (!s_split[j])
				// return (free_tabtab(s_split), NULL);
			ft_copy(s_split[j], s + i, c);
			i += k;
			j++;
		}
	}
	s_split[j] = NULL;
	return (s_split);
}