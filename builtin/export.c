/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:23:31 by ykissiko          #+#    #+#             */
/*   Updated: 2023/07/25 17:23:32 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(t_minishell *mini)
{
	int			i;
	t_builtin	built;

	built.env_size = mini->env_size;
	built.env = ft_set_env(mini->env, mini->env_size, mini->env_size);
	if (!mini->cmd[1])
	{
		ft_sort_export(&built);
		i = -1;
		while (++i < built.env_size)
			printf("declare -x %s\n", built.env[i]);
	}
	else
	{
		built.input = ft_strdup2(mini->input, "export");
		ft_add_export(&built);
		ft_free_array_char(mini->env, mini->env_size);
		mini->env = ft_set_env(built.env, built.env_size, built.env_size);
		mini->env_size = built.env_size;
	}
	ft_free_array_char(built.env, built.env_size);
}


void	ft_sort_export(t_builtin *built)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (++i < built->env_size)
	{
		j = i;
		while (++j < built->env_size)
		{
			if (!built->env[j])
				ft_swap(&built->env[j], &built->env[built->env_size - 1]);
			k = 1;
			if (built->env[i][0] > built->env[j][0])
				ft_swap(&built->env[i], &built->env[j]);
			else if (built->env[i][0] == built->env[j][0])
			{
				while (built->env[i][k] == built->env[j][k])
					k++;
				if (built->env[i][k] > built->env[j][k])
					ft_swap(&built->env[i], &built->env[j]);
			}
		}
	}
}

void	ft_swap(char **s1, char **s2)
{
	char	**temp;

	temp = malloc(sizeof(char *) * (ft_strlen(*s1) + 1));
	if (!temp)
		return ;
	*temp = *s1;
	*s1 = *s2;
	*s2 = *temp;
	free(temp);
}
