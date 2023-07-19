/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:13:38 by ykissiko          #+#    #+#             */
/*   Updated: 2022/10/13 15:49:01 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
			j++;
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (j);
}

static int	low_count(char const *s, char c, int index)
{
	int	count;

	count = 0;
	while (s[index] && s[index] != c)
	{
		count++;
		index++;
	}
	return (count);
}

static char	*set_str(char const *s, int index, char c)
{
	int		i;
	char	*str;

	str = malloc(sizeof(char) * (low_count(s, c, index) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[index + i] && s[index + i] != c)
	{
		str[i] = s[index + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	int		i;
	int		j;
	char	**str;

	count = ft_count(s, c);
	str = malloc(sizeof(char *) * (count + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			str[j++] = set_str(s, i, c);
		while (s[i] && s[i] != c)
			i++;
	}
	str[j] = 0;
	return (str);
}
