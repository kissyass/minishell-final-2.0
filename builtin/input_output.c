/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:03:27 by ykissiko          #+#    #+#             */
/*   Updated: 2023/07/25 17:03:29 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_output_len(char *cmd, char *str)
{
	char	**cmds;
	int		i;
	int		j;
	int		k;

	cmds = ft_split(cmd, ' ');
	i = 0;
	k = -1;
	while (cmds[++k])
	{
		j = -1;
		i = ft_space_check(i, str);
		if (str[i] == ' ')
			i++;
		while (str[i] == cmds[k][++j])
			i++;
		i = ft_space_check(i, str);
		if (str[i] == ' ')
			i++;
	}
	return (i);
}

void	ft_output(t_builtin *built, char quote)
{
	int	i;

	i = built->start - 1;
	while (++i < built->end)
	{
		if (built->input[i] != '\\')
			built->output = ft_charcat(built->output, built->input[i]);
		else
			i = ft_backslash(built, i, quote);
	}
}

int	ft_check_input(t_builtin *built)
{
	int	i;

	i = -1;
	while (built->input[++i])
	{
		ft_quote(built, 0, 0);
		if (built->input[i] == '\'')
			i = ft_quotes_index(built, i, '\'');
		else if (built->input[i] == '"')
			i = ft_quotes_index(built, i, '"');
		else
		{
			i = ft_space_check(i, built->input);
			built->output = ft_charcat(built->output, built->input[i]);
		}
		if (i == -1)
			return (0);
	}
	return (1);
}

int	ft_backslash(t_builtin *built, int i, char quote)
{
	int	backslash;

	backslash = 1;
	while (++i < built->end && built->input[i] == '\\')
		backslash++;
	if (built->input[i] == quote && backslash % 2 == 1)
		backslash--;
	if (backslash == 0)
		backslash = 0;
	else if (backslash % 4 == 0)
		backslash = backslash / 4;
	else
		backslash = backslash / 4 + 1;
	while (--backslash >= 0)
		built->output = ft_charcat(built->output, '\\');
	i--;
	return (i);
}

int	ft_export_output(t_builtin *built, char *cmd)
{
	int	i;

	i = -1;
	if (!built->input[0] || (built->input[0] >= '0' && built->input[0] <= '9'))
		return (printf("%s: '%s': not a valid identifier\n", cmd,
				built->input));
	while (built->input[++i])
	{
		if (built->input[i] == '"' || built->input[i] == '\'')
		{
			i++;
			built->end = ft_check_quotes(built, i, built->input[i - 1]);
			if (built->quote == 1 || built->dquote == 1)
				return (printf("Minishell: syntax error with open quotes\n"));
			i--;
			while (++i < built->end)
				built->output = ft_charcat(built->output, built->input[i]);
			i++;
		}
		if (!built->input[i] || built->input[i] == ' ')
			break ;
		else
			built->output = ft_charcat(built->output, built->input[i]);
	}
	return (0);
}
