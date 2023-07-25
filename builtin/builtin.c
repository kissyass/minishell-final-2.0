/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:07:56 by ykissiko          #+#    #+#             */
/*   Updated: 2023/07/25 17:07:59 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>
#include <errno.h>
// check if redirect exists, and if exists, set fds according to redirect types
int check_redirects(char **args,int *fds){
    int i = 0;
    int fd;
    while (args && args[i]){
        // redirect out
        if (ft_strcmp(">>",args[i])){

            // check if args[i+1] exists
            args[i] = NULL;
            fd = open(args[i+2], O_WRONLY | O_CREAT, 0777);
            printf("ERROR: %s\n", strerror(errno));
            if (fd >= 0)
            {
                printf("naber baby \n");
                fds[1] = fd;
            }
            return 1;
        }
        else if (ft_strcmp(">",args[i])){
            // check if args[i+1] exists
            args[i] = NULL;
            fd = open(args[i+1], O_WRONLY | O_CREAT, 0777);
            if (fd >= 0)
                fds[1] = fd;
            return 1;
        }
        // redirect in
        else if (ft_strcmp("<",args[i])){
            // check if args[i+1] exists
            args[i] = NULL;
            fd = open(args[i+1], O_RDONLY);
            if (fd >= 0)
                fds[0] = fd;
            return 1;
        }
        // heredoc
        else if (ft_strcmp("<<",args[i])){
            // HANDLE HEREDOC
            return 1;
        }
        i++;
    }
    return 0;
}

void ft_builtin(t_minishell *mini)
{
    // int fds_rec[2];
    // int fds_red[2];

    // (fds_red[0] = -1, fds_red[1] = -1);
    // (fds_rec[0] = -1, fds_rec[1] = -1);

    //printf("NEREDESIN BRE GAFI\n");
    mini->cmd = ft_split(mini->input, ' ');


    // if (check_redirects(mini->cmd, fds_red)){

    //     if (fds_red[0] != -1)
    //     {
    //         fds_rec[0] = dup(0);
    //         if (dup2(0,fds_red[0]) == -1 && close(fds_red[0]))
    //         { /* exit */ }
    //     }
    //     if (fds_red[1] != -1)
    //     {
    //         printf("NEREDESIN BRE GAFIL\n");
    //         fds_rec[1] = dup(1);
    //         if (dup2(1,fds_red[1]) == -1 && close(fds_red[1]))
    //         { /* exit */ }

    //     }
    // }

    if (ft_cmdcmp(mini->cmd[0], "echo"))
        ft_echo(mini);
    /*else if (ft_strcmp(mini->cmd[0], "cd"))
        ft_cd(mini);
    else if (ft_strcmp(mini->cmd[0], "pwd"))
        ft_pwd(mini);
    else if (ft_strcmp(mini->cmd[0], "export"))
        ft_export(mini);
    else if (ft_strcmp(mini->cmd[0], "unset"))
        ft_unset(mini);
    else if (ft_strcmp(mini->cmd[0], "env"))
        ft_env(mini->env);
    else if (ft_strcmp(mini->cmd[0], "exit"))
        ft_exit(mini);*/
    else
        ft_execute_cmds(mini->cmd, mini->env);
    ft_free_array_char(mini->cmd, ft_count(mini->input, ' '));






    //printf("NEREDESIN BRE GFI\n");
    // recover standard inputs
    // if (fds_rec[0] != -1)
    //     if (dup2(0,fds_rec[0]) == -1 && close(fds_rec[0] == -1))
    //         { /* exit */ }
    // if (fds_rec[1] != -1)
    //     if (dup2(1,fds_rec[1]) == -1  && close(fds_rec[0] == -1))
            { /* exit */ }
}
