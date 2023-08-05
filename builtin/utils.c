/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:22:05 by ykissiko          #+#    #+#             */
/*   Updated: 2023/08/02 17:22:07 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if ((!s1 && !s2))
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_cmdcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_charcat(char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	if (s)
		i = ft_strlen(s);
	str = ft_calloc(sizeof(char), (i + 2));
	if (!str)
		return (NULL);
	if (s)
	{
		i = -1;
		while (s[++i])
			str[i] = s[i];
	}
	str[i] = c;
	str[i + 1] = 0;
	if (s)
		free(s);
	return (str);
}

char	*ft_strdup2(char *str, char *cmd)
{
	char	*s;
	int		i;
	int		j;

	i = ft_output_len(cmd, str);
	j = ft_strlen(str);
	s = ft_calloc(sizeof(char), (j + 1));
	if (!s)
		return (NULL);
	i--;
	j = -1;
	while (str[++i])
		s[++j] = str[i];
	s[++j] = 0;
	return (s);
}

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a'
			&& c <= 'z') || c == '_' || c == '"' || c == '\'' || c == '\\')
		return (1);
	return (0);
}
