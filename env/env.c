/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeroglu <aeroglu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:11:12 by ykissiko          #+#    #+#             */
/*   Updated: 2023/08/06 04:17:23 by aeroglu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(void)
{
	int	i;

	i = -1;
	while (++i < g_ms.env_size)
		printf("%s\n", g_ms.env[i]);
}

void	ft_env_add(t_builtin *built)
{
	t_builtin	env_built;

	env_built.output = ft_strdup(built->output);
	env_built.env_size = g_ms.env_size;
	env_built.env = ft_set_env(g_ms.env, g_ms.env_size, g_ms.env_size);
	env_built.var = ft_calloc(sizeof(char), 1);
	if (!env_built.var)
		return ;
	ft_export_check(&env_built, 0);
	ft_free_array_char(g_ms.env, g_ms.env_size);
	g_ms.env = ft_set_env(env_built.env, env_built.env_size,
			env_built.env_size);
	g_ms.env_size = env_built.env_size;
	free(env_built.output);
	free(env_built.var);
	ft_free_array_char(env_built.env, env_built.env_size);
}
