/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeroglu <aeroglu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 19:16:54 by aeroglu           #+#    #+#             */
/*   Updated: 2023/07/30 19:13:51 by aeroglu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_ms;

void	init_app(char **env)
{
	errno = 0;
	g_ms.paths = NULL;
	g_ms.parent_pid = getpid();
	g_ms.env_size = ft_strlen_double(env);
	g_ms.env = ft_set_env(env, g_ms.env_size, g_ms.env_size);
	g_ms.exp_size = ft_strlen_double(env);
	g_ms.exp = ft_set_env(env, g_ms.env_size, g_ms.env_size);
	//printf("sizes env %d, exp %d\n", g_ms.env_size, g_ms.exp_size);
	set_paths();
}

void	init_shell(char *input)
{
	g_ms.token = NULL;
	g_ms.process = NULL;
	g_ms.process_count = 0;
	tokenize(input);
	if (!lexer())
		return ;
	start_cmd();
}

void	ctrl_c(int sig)
{
	(void)sig;
	g_ms.ignore = TRUE;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	write(1, "\033[A", 3);
}

void	ctrl_d(char *input)
{
	if (!input)
	{
		printf("exit\n");
		exit(errno);
	}
}

int	main(int argc, char **argv, char **envp)
{
	init_app(envp);
	rl_bind_key('\t', rl_complete);
	while (argc && argv)
	{
		g_ms.ignore = FALSE;
		signal(SIGINT, &ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		write(1, "\033[32m", 5);
		g_ms.input = readline("minishell_> ");
		write(1, "\033[0m", 4);
		ctrl_d(g_ms.input);
		if (g_ms.ignore)
		{
			free(g_ms.input);
			g_ms.input = malloc(1);
		}
		if (g_ms.input[0])
		{
			init_shell(g_ms.input);
			add_history(g_ms.input);
		}
		free(g_ms.input);
	}
	ft_free_array_char(g_ms.env, g_ms.env_size);
	exit(errno);
}
