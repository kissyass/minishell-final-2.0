/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeroglu <aeroglu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:12:04 by ykissiko          #+#    #+#             */
/*   Updated: 2023/08/06 01:43:09 by aeroglu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(void)
{
	if (!g_ms.cmd[1])
		return ;
	if (g_ms.cmd[1][0] != '~')
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
	char	*result;

	result = getcwd((void *)0, 0);
	if (!result)
		perror("minishell ");
	else
		printf("%s\n", result);
	free(result);
	if (!is_parent())
		exit(g_ms.exit_code);
}
