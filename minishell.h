#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <limits.h>
#include <sys/wait.h>

# include "libft/libft.h"

typedef struct s_minishell
{
    char **env;
    int env_size;
    char *input;
    char **cmd;
} t_minishell;

typedef struct s_pipes
{
    int cmd_num;
    pid_t *pid;
    int **fd;
    char **input;
    char **cmd;

}   t_pipes;

typedef struct s_builtin
{
    char *input;
    int quote;
    int dquote;
    char *output;
    int start;
    int end;
    //int bslash;
} t_builtin;


//UTILS
int ft_strlen_double(char **str);
int ft_execute_cmds(char **cmd, char **env);
char *ft_strcat(char *s1, char *s2);
void ft_free_array_char(char **arr, int size);
void ft_free_array_int(int **arr, int size);

//ENV
//set_env
char **ft_set_env(char **envp, int size);

//PIPES
void ft_pipes(t_minishell *mini);
void ft_close(t_pipes *pipes, int i);
void ft_dup2(t_pipes *pipes, t_minishell *mini, int i);
void set_pipes(t_pipes *pipes, t_minishell *mini, int set);
void ft_perror(char *error);

//BUILTIN
//builtin
void ft_builtin(t_minishell *mini);
//echo
void ft_echo(t_minishell *mini);
int ft_check_input(t_builtin *built);
int ft_check_quotes(t_builtin *built, int index, char quote);
void ft_quote(t_builtin *built, char quote, int type);
char *ft_charcat(char *s, char c);
void ft_output(t_builtin *built, char quote);

//utils
int	ft_strcmp (char *s1, char *s2);


#endif