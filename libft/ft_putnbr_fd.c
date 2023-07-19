/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:07:26 by ykissiko          #+#    #+#             */
/*   Updated: 2022/10/13 15:45:24 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	putposnbr(int n, int fd)
{
	int		num;
	char	c;

	if (n > 9)
	{
		num = n / 10;
		putposnbr(num, fd);
		c = 48 + n % 10;
		ft_putchar_fd(c, fd);
	}
	else
	{
		c = 48 + n % 10;
		ft_putchar_fd(c, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		n = 147483648;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	putposnbr(n, fd);
}
