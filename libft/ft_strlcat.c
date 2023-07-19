/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 13:08:47 by ykissiko          #+#    #+#             */
/*   Updated: 2022/10/16 11:42:45 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	srcsize;

	i = 0;
	srcsize = ft_strlen(src);
	if (dstsize == 0)
		return (srcsize);
	j = ft_strlen(dest);
	if (dstsize <= j)
		return (srcsize + dstsize);
	while (src[i] != '\0' && i < dstsize - j - 1)
	{
		dest[i + j] = src[i];
		i++;
	}	
	dest[i + j] = '\0';
	return (j + srcsize);
}
