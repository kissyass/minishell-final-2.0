/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeroglu <aeroglu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:02:13 by aeroglu           #+#    #+#             */
/*   Updated: 2023/08/04 22:01:43 by aeroglu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_set_env(char **envp, int new_size, int old_size)
{
	char	**env;
	int		i;

	//env = malloc(sizeof(char *) * (new_size + 1));
	//ft_memset(env,0,sizeof(char *) * (new_size + 1));
	env = ft_calloc(sizeof(char *), new_size);
	if (!env)
		return (NULL);
	i = -1;
	if (new_size > old_size)
	{
		while (++i < old_size)
			env[i] = ft_strdup(envp[i]);
		i--;
		// while (++i < new_size)
		// 	env[i] = NULL;
	}
	else
	{
		while (++i < new_size)
			env[i] = ft_strdup(envp[i]);
	}
	return (env);
}

void	set_env(char **env)
{
	size_t	i;
	size_t	len;
	char	**head;

	head = env;
	while (*head)
		head++;
	len = head - env;
	g_ms.env = ft_calloc(sizeof(char **), len + 1);
	i = -1;
	while (++i < len)
		g_ms.env[i] = ft_strdup(env[i]);
}

char	*split_env(char *str)
{
	while (*str != '=')
		str++;
	str++;
	return (ft_strdup(str));
}

char	*get_env(char *str)
{
	size_t	len;
	char	**env;
	char	*new_str;

	env = g_ms.env;
	new_str = ft_strjoin(str, "=");
	len = ft_strlen(new_str);
	while (*env)
	{
		if (!ft_strncmp(*env, new_str, len))
		{
			free(new_str);
			return (split_env(*env));
		}
		env++;
	}
	free(new_str);
	return (ft_calloc(sizeof(char *), 1));
}
