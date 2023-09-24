/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeroglu <aeroglu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 04:14:31 by aeroglu           #+#    #+#             */
/*   Updated: 2023/08/06 04:14:49 by aeroglu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_flag(char **str)
{
	int	i;
	int	j;

	i = 1;
	g_ms.flag = 0;
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
				{
					i++;
					g_ms.flag = 1;
				}
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
