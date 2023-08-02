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

void ft_unset(t_minishell *mini)
{
	t_builtin built;

	built.env_size = mini->env_size;
	built.env = ft_set_env(mini->env, mini->env_size, mini->env_size);
	if (mini->cmd[1])
	{
		built.input = ft_strdup2(mini->input, "unset");
		built.output = malloc(sizeof(char));
        built.var = malloc(sizeof(char));
		if (!built.output || !built.var)
			return ;
		if (ft_export_output(&built, "export") != 0)
			return ;
		ft_export_check(&built, 2);
		ft_sort_export(&built);
        ft_free_array_char(mini->env, mini->env_size);
		mini->env = ft_set_env(built.env, built.env_size, built.env_size);
		mini->env_size = built.env_size;
        ft_free_array_char(built.env, built.env_size);
	}
}

void ft_unset_update(t_builtin *built, int index)
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