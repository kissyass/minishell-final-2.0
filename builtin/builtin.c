/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeroglu <aeroglu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:07:56 by ykissiko          #+#    #+#             */
/*   Updated: 2023/08/02 17:17:18 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *command)
{
	if (ft_cmdcmp(command, "cd"))
		return (1);
	if (ft_cmdcmp(command, "env"))
		return (1);
	if (ft_cmdcmp(command, "pwd"))
		return (1);
	if (ft_cmdcmp(command, "echo"))
		return (1);
	if (ft_cmdcmp(command, "exit"))
		return (1);
	if (ft_cmdcmp(command, "unset"))
		return (1);
	if (ft_cmdcmp(command, "export"))
		return (1);
	return (0);
}

void	ft_builtin(void)
{
	g_ms.cmd = ft_split(g_ms.input, ' ');
	if (g_ms.cmd[0] && ft_cmdcmp(g_ms.cmd[0], "echo"))
		ft_echo();
	else if (ft_cmdcmp(g_ms.cmd[0], "cd"))
		ft_cd();
	else if (ft_cmdcmp(g_ms.cmd[0], "pwd"))
		ft_pwd();
	else if (ft_cmdcmp(g_ms.cmd[0], "export"))
		ft_export();
	else if (ft_cmdcmp(g_ms.cmd[0], "unset"))
		ft_unset();
	else if (ft_cmdcmp(g_ms.cmd[0], "env"))
		ft_env();
	else if (ft_cmdcmp(g_ms.cmd[0], "exit"))
		ft_exit();
	ft_free_array_char(g_ms.cmd, ft_count(g_ms.input, ' '));
}
