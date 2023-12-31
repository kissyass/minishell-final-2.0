/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:29:17 by ykissiko          #+#    #+#             */
/*   Updated: 2023/08/02 17:30:10 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_execute_cmds(char **cmd, char **env)
{
	char	*path;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		path = cmd[0];
		execve(path, cmd, env);
		path = ft_strcat("/bin/", cmd[0]);
		execve(path, cmd, env);
		path = ft_strcat("/usr/bin/", cmd[0]);
		execve(path, cmd, env);
	}
	else if (pid < 0)
		ft_perror("fork");
	else
	{
		waitpid(pid, &status, 0);
	}
	return (-1);
}

char	*ft_strcat(char *s1, char *s2)
{
	int		len;
	int		i;
	char	*str;

	len = 0;
	if (s1)
		len = ft_strlen(s1);
	len += ft_strlen(s2);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = -1;
	if (s1)
	{
		while (s1[++i])
			str[i] = s1[i];
	}
	len = i;
	i = -1;
	while (s2[++i])
		str[len + i] = s2[i];
	str[len + i] = 0;
	return (str);
}

void	ft_free_array_char(char **arr, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(arr[i]);
	free(arr);
}

void	ft_free_array_int(int **arr, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(arr[i]);
	free(arr);
}
