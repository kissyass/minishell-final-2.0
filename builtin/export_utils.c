/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeroglu <aeroglu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 13:34:40 by ykissiko          #+#    #+#             */
/*   Updated: 2023/08/06 04:53:07 by aeroglu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export_check(t_builtin *built, int cmd)
{
	int	i;

	i = -1;
	while (built->output[++i])
	{
		if (built->output[i] == '=' && cmd <= 1)
			break ;
		if (ft_isalnum(built->output[i]))
			built->var = ft_charcat(built->var, built->output[i]);
		else
			return (printf("export: '%s': not a valid identifier\n",
					built->output));
	}
	if (!ft_old_var(built, i, cmd) && cmd <= 1)
	{
		ft_export_var(built, i, cmd);
		built->env = ft_set_env(built->env, built->env_size + 1,
				built->env_size);
		built->env_size++;
		built->env[built->env_size - 1] = ft_strdup(built->var);
	}
	return (0);
}

void	ft_export_var(t_builtin *built, int i, int cmd)
{
	if (built->output[i] && cmd == 1)
	{
		built->var = ft_charcat(built->var, built->output[i]);
		built->var = ft_charcat(built->var, '"');
		while (built->output[++i])
			built->var = ft_charcat(built->var, built->output[i]);
		built->var = ft_charcat(built->var, '"');
	}
	else if (built->output[i] && cmd == 0)
	{
		built->var = ft_charcat(built->var, built->output[i]);
		while (built->output[++i])
			built->var = ft_charcat(built->var, built->output[i]);
	}
}

int	ft_old_var(t_builtin *built, int index, int cmd)
{
	int		i;
	char	**name;

	i = -1;
	while (++i < built->env_size)
	{
		name = ft_split(built->env[i], '=');
		if (ft_cmdcmp(name[0], built->var))
		{
			ft_export_var(built, index, cmd);
			if (cmd <= 1)
			{
				free(built->env[i]);
				built->env[i] = ft_strdup(built->var);
			}
			if (cmd == 2)
				ft_unset_update(built, i);
			ft_free_array_char(name, ft_strlen_double(name));
			return (1);
		}
		else
			ft_free_array_char(name, ft_strlen_double(name));
	}
	return (0);
}

int	ft_add_export(t_builtin *built)
{
	ft_quote(built, 0, 0);
	built->end = 0;
	built->output = ft_calloc(sizeof(char), 1);
	built->var = ft_calloc(sizeof(char), 1);
	if (!built->output || !built->var)
		return (0);
	if (ft_export_output(built, "export") != 0)
		return (0);
	if (ft_export_check(built, 1) == 0 && ft_strchr(built->output, '='))
		ft_env_add(built);
	free(built->output);
	free(built->var);
	free(built->input);
	return (0);
}
