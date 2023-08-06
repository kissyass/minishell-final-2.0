/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeroglu <aeroglu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:06:43 by ykissiko          #+#    #+#             */
/*   Updated: 2023/08/06 05:33:45 by aeroglu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(void)
{
	t_builtin	built;

	built.input = ft_calloc(sizeof(char), 1);
	built.output = ft_calloc(sizeof(char), 1);
	if (!built.output || !built.input)
		return ;
	if ((g_ms.cmd[1]))
	{
		if ((ft_cmdcmp(g_ms.cmd[1], "-n") && g_ms.cmd[2])
			|| !ft_cmdcmp(g_ms.cmd[1], "-n"))
		{
			built.input = ft_strdup2(g_ms.input,
					echo_cmd(skip_flag(g_ms.process->execute)));
			if (!ft_check_input(&built))
			{
				free(built.input);
				return ;
			}
			printf("%s", built.output);
		}
	}
	if (g_ms.cmd[1] && !ft_cmdcmp(g_ms.cmd[1], "-n"))
		printf("\n");
	free(built.input);
	free(built.output);
}

int	is_alnum(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9') || c == '_')
		return (1);
	return (0);
}

int	echo_dollar_ft(int index, t_builtin *built, char *var)
{
	char	**name;
	char	*var;
	int		i;
	int		j;
	int		i;

	while (built->input[++index] && is_alnum(built->input[index]))
		var = ft_charcat(var, built->input[index]);
	index--;
	i = -1;
	while (g_ms.env[++i])
	{
		name = ft_split(g_ms.env[i], '=');
		if (ft_cmdcmp(name[0], var))
		{
			j = 0;
			while (name[++j])
				built->output = ft_strcat(built->output, name[j]);
			break ;
		}
		ft_free_array_char(name, ft_count(g_ms.env[i], '='));
	}
	return (index);
}

int	ft_dollar_echo(int index, t_builtin *built)
{
	char	*var;

	var = ft_calloc(sizeof(char), 1);
	if (built->input[index + 1] == '?')
	{
		built->output = ft_strcat(built->output, ft_itoa(g_ms.exit_code));
		index += 2;
	}
	else if (!built->input[index + 1] || !is_alnum(built->input[index + 1]))
		built->output = ft_charcat(built->output, built->input[index]);
	else
	{
		index = echo_dollar_ft(index, built, var);
	}
	return (index);
}

char	*echo_cmd(int index)
{
	char	*str;
	int		i;

	str = ft_calloc(sizeof(char), 1);
	i = -1;
	while (++i < index)
	{
		str = ft_strcat(str, g_ms.process->execute[i]);
		str = ft_charcat(str, ' ');
	}
	return (str);
}
