/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeroglu <aeroglu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:06:43 by ykissiko          #+#    #+#             */
/*   Updated: 2023/07/28 19:24:32 by aeroglu          ###   ########.fr       */
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
		if ((ft_cmdcmp(g_ms.cmd[1], "-n") && g_ms.cmd[2]) || !ft_cmdcmp(g_ms.cmd[1], "-n"))
		{
			built.input = ft_strdup2(g_ms.input, echo_cmd(skip_flag(g_ms.process->execute)));
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

int is_alnum(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

int ft_dollar_echo(int index, t_builtin *built)
{
	char *var;
	char **name;
	int j;

	var = ft_calloc(sizeof(char), 1);
	if (built->input[index + 1] == '?')
	{
		built->output = ft_strcat(built->output, ft_itoa(g_ms.status));
		index += 2;
	}
	else if (!built->input[index + 1] || !is_alnum(built->input[index + 1]))
		built->output = ft_charcat(built->output, built->input[index]);
	else
	{
		while (built->input[++index] && is_alnum(built->input[index]))
			var = ft_charcat(var, built->input[index]);
		index--;
		int i = -1;
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
	}
	return (index);
}

char *echo_cmd(int index)
{
	char *str;
	int i;

	str = ft_calloc(sizeof(char), 1);
	i = -1;
	while (++i < index)
	{
		str = ft_strcat(str, g_ms.process->execute[i]);
		str = ft_charcat(str, ' ');
	}
	return (str);
}

int	skip_flag(char **str)
{
	int	i;
	int	j;
	i = 1;
	while (str[i])
	{
		if (str[i][0] == '-' && str[i][0])
		{
			j = 1;
			while (str[i][j] == 'n' && str[i][j])
				j++;
			if (str[i][j] == '\0')
			{
				if (j > 1 && str[i][j - 1] == 'n')
					i++;
			}
			else
				return (i);
		}
		else
			return (i);
	}
	return (i);
}

int	ft_quotes_index(t_builtin *built, int index, char quote)
{
	built->start = index + 1;
	index = ft_check_quotes(built, index + 1, quote);
	built->end = index;
	if (built->dquote == 0 && built->quote == 0)
		ft_output(built, quote);
	else if (built->quote == 1 || built->dquote == 1)
	{
		printf("Minishell: syntax error with open quotes\n");
		return (-1);
	}
	return (index);
}

int	ft_space_check(int index, char *input)
{
	int	i;

	i = index;
	while ((input[index] >= 9 && input[index] <= 13) || input[index] == 32)
		index++;
	if (i < index)
		index--;
	return (index);
}

int	ft_check_quotes(t_builtin *built, int index, char quote)
{
	int	i;
	int	backslash;

	while (built->input[index] && built->input[index] != quote)
		index++;
	i = index;
	backslash = 0;
	if (built->input[index] == quote)
	{
		while (built->input[--i] && built->input[i] == '\\')
			backslash++;
		if (backslash > 0 && backslash % 2 == 1 && (index
				+ 1) != ft_strlen(built->input))
			index = ft_check_quotes(built, index + 1, quote);
		else if (backslash > 0 && backslash % 2 == 1 && (index
				+ 1) == ft_strlen(built->input))
			ft_quote(built, quote, 1);
	}
	if (!built->input[index])
		ft_quote(built, quote, 1);
	return (index);
}

void	ft_quote(t_builtin *built, char quote, int type)
{
	if (type == 0)
	{
		built->quote = 0;
		built->dquote = 0;
	}
	if (type == 1)
	{
		if (quote == '\'')
			built->quote = 1;
		else
			built->dquote = 1;
	}
}
