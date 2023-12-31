/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeroglu <aeroglu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:02:13 by aeroglu           #+#    #+#             */
/*   Updated: 2023/08/06 04:50:24 by aeroglu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_set_env(char **envp, int new_size, int old_size)
{
	char	**env;
	int		i;

	env = ft_calloc(sizeof(char *), new_size);
	if (!env)
		return (NULL);
	i = -1;
	if (new_size > old_size)
	{
		while (++i < old_size)
			env[i] = ft_strdup(envp[i]);
		i--;
	}
	else
	{
		while (++i < new_size)
			env[i] = ft_strdup(envp[i]);
	}
	return (env);
}

char	*exp_dup(char *s)
{
	int		i;
	char	*str;

	str = ft_calloc(sizeof(char), 1);
	i = -1;
	while (s[++i] && s[i] != '=')
		str = ft_charcat(str, s[i]);
	str = ft_strcat(str, "=\"");
	while (s[++i])
		str = ft_charcat(str, s[i]);
	str = ft_charcat(str, '"');
	return (str);
}

char	**ft_set_exp(char **envp, int new_size, int old_size)
{
	char	**env;
	int		i;

	env = ft_calloc(sizeof(char *), new_size);
	if (!env)
		return (NULL);
	i = -1;
	if (new_size > old_size)
	{
		while (++i < old_size)
			env[i] = exp_dup(envp[i]);
		i--;
	}
	else
	{
		while (++i < new_size)
			env[i] = exp_dup(envp[i]);
	}
	return (env);
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
