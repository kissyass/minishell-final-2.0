/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeroglu <aeroglu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:07:56 by ykissiko          #+#    #+#             */
/*   Updated: 2023/07/28 19:23:48 by aeroglu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_builtin(char *command)
{
    if (ft_strcmp(command, "cd"))
        return (CD);
    if (ft_strcmp(command, "env"))
        return (ENV);
    if (ft_strcmp(command, "pwd"))
        return (PWD);
    if (ft_strcmp(command, "echo"))
        return (ECHO);
    if (ft_strcmp(command, "exit"))
        return (EXIT);
    if (ft_strcmp(command, "unset"))
        return (UNSET);
    if (ft_strcmp(command, "export"))
        return (EXPORT);
    return (0);
}

void ft_builtin(t_minishell *mini)
{
    mini->cmd = ft_split(mini->input, ' ');
    if (mini->cmd[0] && ft_cmdcmp(mini->cmd[0], "echo"))
        ft_echo(mini);
    else if (ft_cmdcmp(mini->cmd[0], "cd"))
        ft_cd(mini);
    else if (ft_cmdcmp(mini->cmd[0], "pwd"))
        ft_pwd(mini);
    else if (ft_cmdcmp(mini->cmd[0], "export"))
        ft_export(mini);
    else if (ft_cmdcmp(mini->cmd[0], "unset"))
        ft_unset(mini);
    // else if (ft_cmdcmp(mini->cmd[0], "env"))
    //     ft_env(mini->env);
    // else if (ft_cmdcmp(mini->cmd[0], "exit"))
    //     ft_exit(mini);
    else
        ft_execute_cmds(mini->cmd, mini->env);
    ft_free_array_char(mini->cmd, ft_count(mini->input, ' '));
}
