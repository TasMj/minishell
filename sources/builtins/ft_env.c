/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:11:48 by tas               #+#    #+#             */
/*   Updated: 2023/05/25 12:38:27 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

// t_list  **get_list_env(char **env)
// {
    // int i;
    // char    cwd[1024];
    // t_list  **list_env;
// 
    // // i = 0;
    // // list_env = malloc(sizeof(t_list));
    // // ft_memset(list_env, 0, sizeof(t_list));
    // // while (env[i] != NULL)
    // // {
        // // add_list(list_env, env[i]);
        // // i++;
    // }
    // if (ft_lstsize(list_env) == 0)
    // {
    //     cwd = getcwd(cwd, sizeof(cwd));
    //     add_list(list_env, ft_strjoin("PWD=", cwd));
    //     add_list(list_env, ft_strjoin("PATH=", "/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"))
    // }
    // return (list_env);
// }

t_list	**get_list_env(char **env)
{
	int		i;
	t_list	**list_env;

	i = 0;
	list_env = malloc(sizeof(t_list));
	ft_memset(list_env, 0, sizeof(t_list));
	while (env[i] != NULL)
	{
		add_list(list_env, env[i], 0);
		i++;
	}
	return (list_env);
}

int	ft_env(t_list **l)
{
	t_list	*tmp;
	t_list	*tmp_cmd;

	tmp_cmd = *l;
	if ((*l)->next != NULL)
	{
		printf("env: ‘%s’: No such file or directory\n", (*l)->next->content);
		*l = tmp_cmd;
		return (1);
	}
	tmp = *list_ENVI;
	while (*list_ENVI != NULL)
	{
		printf("%s\n", (*list_ENVI)->content);
		(*list_ENVI) = (*list_ENVI)->next;
	}
	*list_ENVI = tmp;
	return (0);
}
