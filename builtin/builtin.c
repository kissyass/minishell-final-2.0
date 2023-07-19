#include "../minishell.h"

void ft_builtin(t_minishell *mini)
{
    mini->cmd = ft_split(mini->input, ' ');
    if (ft_strcmp(mini->cmd[0], "echo"))
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
}
