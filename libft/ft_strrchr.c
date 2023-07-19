/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:47:17 by ykissiko          #+#    #+#             */
/*   Updated: 2022/10/15 16:30:54 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*copy;

	i = c / 256;
	c -= i * 256;
	if (!*s && *s != c)
		return (0);
	copy = (char *)s;
	while (*copy)
		copy++;
	if (c != 0)
		copy--;
	while (*copy != c && copy != s)
	{
		copy--;
		if (copy == s && *s != c)
			return (0);
	}
	return ((char *)copy);
}
