#include "../minishell.h"

/*void ft_pipes(t_minishell *mini)
{
    t_pipes pipes;
    int i;

    set_pipes(&pipes, mini, 1);
    i = -1;
    while (++i < pipes.cmd_num - 1)
    {
        if (pipe(pipes.fd[i]) < 0)
            ft_perror("pipe");
    }
    i = -1;
    while (++i < pipes.cmd_num)
    {
        pipes.cmd = ft_split(pipes.input[i], ' ');
        pipes.pid[i] = fork();
        if (pipes.pid[i] < 0)
            ft_perror("fork");
        if (pipes.pid[i] == 0)
            ft_dup2(&pipes, mini, i);
        else
            ft_close(&pipes, i);
    }
    set_pipes(&pipes, mini, 2);
}

void ft_close(t_pipes *pipes, int i)
{
    if (i > 0)
        close(pipes->fd[i - 1][0]); // close read end of previous pipe
    if (i < pipes->cmd_num - 1)
        close(pipes->fd[i][1]); // close write end of current pipe
    waitpid(pipes->pid[i], NULL, 0); // wait for child process to terminate
}

void ft_dup2(t_pipes *pipes, t_minishell *mini, int i)
{
    if (pipes->pid[i] == 0)
    {
        if (i == 0)
            dup2(pipes->fd[i][1], STDOUT_FILENO);
        else if (i == pipes->cmd_num - 1)
            dup2(pipes->fd[i - 1][0], STDIN_FILENO);
        else
        {
            dup2(pipes->fd[i - 1][0], STDIN_FILENO);
            dup2(pipes->fd[i][1], STDOUT_FILENO);
        }
        if (ft_execute_cmds(pipes->cmd, mini->env) == -1)
            ft_perror("execve");
    }
}

void set_pipes(t_pipes *pipes, t_minishell *mini, int set)
{
    int i;

    if (set == 1)
    {
        pipes->input = ft_split(mini->input, '|');
        pipes->cmd_num = ft_count(mini->input, '|');
        pipes->pid = malloc(sizeof(pid_t) * (pipes->cmd_num));
        pipes->fd = malloc(sizeof(int *) * (pipes->cmd_num - 1));
        if (!pipes->pid || !pipes->fd)
            return ;
        i = -1;
        while (++i < pipes->cmd_num - 1)
            pipes->fd[i] = malloc(sizeof(int) * 2);
    }
    else if (set == 2)
    {
        ft_free_array_char(pipes->input, pipes->cmd_num);
        free(pipes->pid);
        ft_free_array_int(pipes->fd, pipes->cmd_num - 1);
    }
}

void ft_perror(char *error)
{
    perror(error);
    exit(EXIT_FAILURE);
}*/