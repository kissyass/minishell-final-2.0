#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <limits.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

# include "libft/libft.h"

# define TRUE 1
# define FALSE 0
# define DOLLAR_OP '$'
# define DOUBLE_QUOTE '"'
# define SINGLE_QUOTE '\''
# define CHILD_PROCESS 0
# define MAIN_PROCESS 1
# define REPLACE 1
# define APPEND 0

/*enum e_ttype
{
    PIPE = 1,
    STRING,
    HERE_DOC,
    RED_INPUT,
    RED_APPEND,
    RED_OUTPUT
};

typedef struct s_minishell
{
    int parent_pid;
    int procces_count;
    int ignore;
    int env_size;
    char **env;
    char **cmd;
    char **paths;
    char *input;
    t_pipes *process;
} t_minishell;

t_minishell	g_ms;

typedef struct s_pipes
{
    pid_t *pid;
    int fd[2];
    int heredoc_fd[2];
    char **execute;
    char **redirects;
    struct s_pipes *prev;
    struct s_pipes *next;
    int cmd_num;
    char **input;
    char **cmd;

}   t_pipes;*/

typedef struct s_pipes
{
    int cmd_num;
    pid_t *pid;
    int **fd;
    char **input;
    char **cmd;

}   t_pipes;

typedef struct s_minishell
{
    char **env;
    int env_size;
    char *input;
    char **cmd;
} t_minishell;

typedef struct s_builtin
{
    char *input;
    int quote;
    int dquote;
    char *output;
    int start;
    int end;
    char **env;
    int env_size;
} t_builtin;


//free
void	free_array(char *arr);

//UTILS
int ft_strlen_double(char **str);
int ft_execute_cmds(char **cmd, char **env);
char *ft_strcat(char *s1, char *s2);
void ft_free_array_char(char **arr, int size);
void ft_free_array_int(int **arr, int size);

//redirect
void	input(char *file);
void	output(char *file, int mode);

//utils
int	is_operator(char *str);
int	is_parent(void);


//ENV
//set_env
char **ft_set_env(char **envp, int size);
void	set_paths(void);;

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
int ft_check_quotes(t_builtin *built, int index, char quote);
void ft_quote(t_builtin *built, char quote, int type);
int ft_space_check(int index, char *input);
int ft_quotes_index(t_builtin *built, int index, char quote);
//input_output
int ft_output_len(char *cmd, char *str);
int ft_check_input(t_builtin *built);
void ft_output(t_builtin *built, char quote);
int ft_backslash(t_builtin *built, int i, char quote);
//cd_pwd
void ft_cd(t_minishell *mini);
void ft_pwd(t_minishell *mini);
//export
void ft_export(t_minishell *mini);
void ft_sort_export(t_builtin *built);
void ft_swap(char **s1, char **s2);

//utils
int	ft_strcmp (char *s1, char *s2);
int	ft_cmdcmp(char *s1, char *s2);
char *ft_charcat(char *s, char c);
char *ft_strdup2(char *str, char *cmd);


#endif