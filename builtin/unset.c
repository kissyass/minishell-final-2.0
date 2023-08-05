/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:37:07 by ykissiko          #+#    #+#             */
/*   Updated: 2023/08/02 14:37:08 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(void)
{
	t_builtin	built;

	built.env_size = g_ms.env_size;
	built.env = ft_set_env(g_ms.env, g_ms.env_size, g_ms.env_size);
	if (g_ms.cmd[1])
	{
		built.input = ft_strdup2(g_ms.input, "unset");
		built.output = ft_calloc(sizeof(char), 1);
		built.var = ft_calloc(sizeof(char), 1);
		if (!built.output || !built.var)
			return ;
		if (ft_export_output(&built, "export") != 0)
			return ;
		ft_export_check(&built, 2);
		ft_sort_export(&built);
		ft_free_array_char(g_ms.env, g_ms.env_size);
		g_ms.env = ft_set_env(built.env, built.env_size, built.env_size);
		g_ms.env_size = built.env_size;
		ft_free_array_char(built.env, built.env_size);
	}
}

void	ft_unset_update(t_builtin *built, int index)
{
	index--;
	while (++index < built->env_size - 1)
	{
		free(built->env[index]);
		built->env[index] = built->env[index + 1];
	}
	built->env = ft_set_env(built->env, built->env_size - 1, built->env_size);
	built->env_size--;
	free(built->input);
	free(built->output);
	free(built->var);
}
