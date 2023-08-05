/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:12:04 by ykissiko          #+#    #+#             */
/*   Updated: 2023/07/25 17:12:05 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(void)
{
	if (!g_ms.cmd[1])
		return ;
	if (g_ms.cmd[1][0] != '.' && g_ms.cmd[1][0] != '~')
	{
		if (chdir(g_ms.cmd[1]) != 0)
		{
			perror("cd");
			return ;
		}
	}
	else
		printf("Specify absolute or relative path\n");
}

void	ft_pwd(void)
{
	char	*pwd;

	if (g_ms.cmd[1])
	{
		printf("pwd:too many arguments\n");
		return ;
	}
	pwd = ft_calloc(sizeof(PATH_MAX), 1);
	if (!pwd)
		return ;
	getcwd(pwd, PATH_MAX);
	printf("%s\n", pwd);
	free(pwd);
	return ;
}
