/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:38:58 by ykissiko          #+#    #+#             */
/*   Updated: 2022/10/15 16:22:57 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(int n)
{
	int	size;
	int	i;

	size = 1;
	i = 10;
	if (n == -2147483648)
	{
		size += 2;
		n = 147483648;
	}
	else if (n < 0)
	{
		size++;
		n *= -1;
	}
	if (n >= 1000000000)
		return (10);
	while (n >= i)
	{
		size++;
		i *= 10;
	}
	return (size);
}

static char	*set_posstr(int n, int size, char *num)
{
	int		i;

	i = size - 1;
	if (n == 0)
		num[0] = 48;
	while (n > 0)
	{
		num[i] = (n % 10) + 48;
		n /= 10;
		i--;
	}
	num[size] = 0;
	return (num);
}

static char	*set_negstr(int n, int size, char *num)
{
	num[0] = 45;
	if (n == -2147483648)
	{
		num[1] = 50;
		n = -147483648;
	}
	n *= -1;
	num = set_posstr(n, size, num);
	return (num);
}

char	*ft_itoa(int n)
{
	char	*num;
	int		size;

	size = ft_size(n);
	num = malloc(sizeof(char) * (size + 1));
	if (!num)
		return (NULL);
	if (n < 0)
		num = set_negstr(n, size, num);
	else
		num = set_posstr(n, size, num);
	return (num);
}
