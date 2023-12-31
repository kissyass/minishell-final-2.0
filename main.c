/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeroglu <aeroglu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 19:16:54 by aeroglu           #+#    #+#             */
/*   Updated: 2023/08/06 04:50:28 by aeroglu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_ms;

void	init_app(char **env)
{
	g_ms.exit_code = 0;
	g_ms.parent_pid = getpid();
	g_ms.paths = NULL;
	g_ms.env_size = ft_strlen_double(env);
	g_ms.env = ft_set_env(env, g_ms.env_size + 1, g_ms.env_size);
	g_ms.exp_size = ft_strlen_double(env);
	g_ms.exp = ft_set_exp(env, g_ms.exp_size + 1, g_ms.exp_size);
	set_paths();
}

void	main_continue(char *input)
{
	if (ft_pipecheck(input))
		init_shell(input);
	add_history(input);
}

int	main(int ac, char **av, char **env)
{
	init_app(env);
	while (ac && av)
	{
		g_ms.ignore = FALSE;
		signal(SIGQUIT, &ctrl_bs);
		signal(SIGINT, &ctrl_c);
		write(1, "\033[32m", 5);
		g_ms.input = readline("Minishell >>> ");
		write(1, "\033[0m", 4);
		ctrl_d(g_ms.input);
		if (g_ms.ignore)
		{
			free(g_ms.input);
			g_ms.input = malloc(1);
		}
		else if (*input && g_ms.ignore == FALSE)
			main_continue(g_ms.input);
		free(g_ms.input);
	}
	exit(g_ms.exit_code);
}
