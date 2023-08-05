/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeroglu <aeroglu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 19:40:26 by aeroglu           #+#    #+#             */
/*   Updated: 2023/08/06 00:42:08 by aeroglu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_heredoc(int sig)
{
	(void)sig;
	g_ms.ignore = TRUE;
	g_ms.exit_code = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	heredoc(int *fd, char *endline)
{
	//char		*input;
	static int	start = 0;

	if (start)
	{
		start = 1;
		close(fd[0]);
		close(fd[1]);
	}
	if (pipe(fd) < 0)
		return (perror("minishell"));
	while (1)
	{
		signal(SIGINT, &close_heredoc);
		g_ms.input = readline("heredoc>> ");
		printf ("%s\n", endline);
		printf ("%s\n", g_ms.input);
		if (!g_ms.input || ft_strcmp(g_ms.input, endline) || g_ms.ignore)
		{
			free(g_ms.input);
			break ;
		}
		write(fd[1], g_ms.input, ft_strlen(g_ms.input));
		write(fd[1], "\n", 1);
		free(g_ms.input);
	}
	close(fd[1]);
}
