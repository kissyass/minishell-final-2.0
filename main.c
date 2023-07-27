/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeroglu <aeroglu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:29:23 by aeroglu           #+#    #+#             */
/*   Updated: 2023/07/27 17:40:30 by aeroglu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    init_app(char **env)
{
    errno = 0;
    g_ms.paths = NULL;
    g_ms.parent_pid = getpid();
    ft_set_env(env, g_ms.env_size);
    set_paths();
}

void    init_shell(char *input)
{
    g_ms.process = NULL;
    g_ms.process_count = NULL;
    tokenize(input);
    /*if (!lexer())
        return;*/
    start_cmd();
}

int main(int argc, char **argv, char **envp)
{
    //t_minishell mini;#
    char    *input;

    (void)argc;
    (void)argv;
    /*mini.env_size = ft_strlen_double(envp);
    mini.env = ft_set_env(envp, mini.env_size);*/
    init_app(envp);
    rl_bind_key('\t', rl_complete); // Enable tab-completion

    while (argc && argv)
    {
        g_ms.ignore = FALSE;
        write(1, "\033[32m", 5);
		input = readline(">>> ");
		write(1, "\033[0m", 4);
        if (g_ms.ignore)
        {
            free(input);
            input = malloc(1);
        }
        if (*input)
        {
            init_shell(input);
            add_history(input);
        }
        free(input);
    }
    exit(errno);
    /*while (1)
    {
        mini.input = readline(">>> "); // Read user input
        add_history(mini.input); // Add input to history
        if (mini.input[0])
        {
            if (ft_strchr(mini.input, '|'))
                ft_pipes(&mini);
            else
                ft_builtin(&mini);
        }
        free(mini.input);
    }
    ft_free_array_char(mini.env, mini.env_size);*/
    return 0;
}