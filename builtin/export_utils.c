/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:34:40 by ykissiko          #+#    #+#             */
/*   Updated: 2023/08/02 13:34:42 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export_check(t_builtin *built)
{
	int	i;

	i = -1;
	while (built->output[++i] && built->output[i] != '=')
	{
		if (ft_isalnum(built->output[i]))
			built->var = ft_charcat(built->var, built->output[i]);
		else
			return (printf("export: '%s': not a valid identifier\n",
							built->output));
	}
	if (!ft_old_var(built, i))
	{
		ft_export_var(built, i);
		built->env = ft_set_env(built->env, built->env_size + 1,
				built->env_size);
		built->env_size++;
		built->env[built->env_size - 1] = ft_strdup(built->var);
	}
	return (0);
}

void	ft_export_var(t_builtin *built, int i)
{
	if (built->output[i])
	{
		built->var = ft_charcat(built->var, built->output[i]);
		built->var = ft_charcat(built->var, '"');
		while (built->output[++i])
			built->var = ft_charcat(built->var, built->output[i]);
		built->var = ft_charcat(built->var, '"');
	}
}

int	ft_old_var(t_builtin *built, int index)
{
	int		i;
	char	**name;

	i = -1;
	while (++i < built->env_size)
	{
		name = ft_split(built->env[i], '=');
		if (ft_cmdcmp(name[0], built->var))
		{
			ft_export_var(built, index);
			free(built->env[i]);
			built->env[i] = ft_strdup(built->var);
			ft_free_array_char(name, ft_strlen_double(name));
			return (1);
		}
		ft_free_array_char(name, ft_strlen_double(name));
	}
	return (0);
}

int	ft_add_export(t_builtin *built)
{
	ft_quote(built, 0, 0);
	built->end = 0;
	built->output = malloc(sizeof(char));
	built->var = malloc(sizeof(char));
	if (!built->output || !built->var)
		return (0);
	if (ft_export_output(built) != 0)
		return (0);
	ft_export_check(built);
	free(built->output);
	free(built->var);
	free(built->input);
	return (0);
}
