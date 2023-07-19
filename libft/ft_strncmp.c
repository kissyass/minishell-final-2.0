/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:59:04 by ykissiko          #+#    #+#             */
/*   Updated: 2022/10/15 16:28:58 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	s11;
	unsigned char	s22;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		s11 = s1[i];
		s22 = s2[i];
		if (s1[i] != s2[i])
			return (s11 - s22);
		i++;
	}
	return (0);
}
