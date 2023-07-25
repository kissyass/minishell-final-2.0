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

void ft_cd(t_minishell *mini)
{
    if (!mini->cmd[1])
        return ;
    if (mini->cmd[1][0] != '.' && mini->cmd[1][0] != '~' /*&& mini->cmd[1][0] != '\\'*/)
    {
        if (chdir(mini->cmd[1]) != 0)
        {
            perror("cd");
            return ;
        }
    }
    else
        printf("Specify absolute or relative path\n");
}

void ft_pwd(t_minishell *mini)
{
    char *pwd;

    if (mini->cmd[1])
    {
        printf("pwd:too many arguments\n");
        return ;
    }
    pwd = malloc(sizeof(PATH_MAX));
    if (!pwd)
        return ;
    getcwd(pwd, PATH_MAX);
    printf("%s\n", pwd);
    free(pwd);
    return ;
}