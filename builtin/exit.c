/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:18:34 by ykissiko          #+#    #+#             */
/*   Updated: 2023/08/02 16:18:35 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(void)
{
	ft_free_array_char(g_ms.env, g_ms.env_size);
	ft_free_array_char(g_ms.cmd, ft_strlen_double(g_ms.cmd));
	free(g_ms.input);
	printf("exit\n");
	exit(1);
}
