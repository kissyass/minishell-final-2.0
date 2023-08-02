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
# include <dirent.h>
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

enum e_ttype
{
    PIPE = 1,
    STRING,
    HERE_DOC,
    RED_INPUT,
    RED_APPEND,
    RED_OUTPUT
};

enum    e_builtin_types //We need control to builtin types
{
    CD = 1,
    ENV,
    PWD,
    ECHO,
    EXIT,
    UNSET,
    EXPORT
};

typedef struct s_token
{
    char            *str;
    enum e_ttype    type;
    struct s_token  *prev;
    struct s_token  *next;
}   t_token;

typedef struct s_process
{
	pid_t				pid;
	int					fd[2];
	int					heredoc_fd[2];
	char				**execute;
	char				**redirects;
	struct s_process	*prev;
	struct s_process	*next;
}	t_process;

typedef struct s_minishell
{
    int         parent_pid;
    int         process_count;
    int         ignore;
    int         env_size;
    char        **env;
    char        **paths;
    t_token     *token;
    t_process   *process;

    //char **env;
    //int env_size;
    char *input;
    char **cmd;
}               t_minishell;

extern t_minishell	g_ms;


 typedef struct s_pipes
{
    int cmd_num;
    pid_t *pid;
    int **fd;
    char **input;
    char **cmd;

}   t_pipes;

// typedef struct s_minishell
// {
//     char **env;
//     int env_size;
//     char *input;
//     char **cmd;
// } t_minishell;

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
    char *var;
} t_builtin; 

//tokenize
void	tokenize(char *str);

//error
void	token_err(int type);
void	directory_err(char *str);
void	command_err(char *str);
void	no_file_err(char *str);

//lexer
t_process	*init_process(void);
void	process_addback(t_process **process, t_process *new_process);
void	push_new_str(char **new_str, char *str);
char	*clean_quote(char *str);
char	**push_array(char **arg_arr, char *str);
int	    lexer(void);
char	*dollar(char *str);

//cmd
void	close_all_fd(void);
void	start_cmd(void);
void	run_cmd(t_process *process);

//tokenize
int	token_addback(t_token **token, t_token *new_token, int plus);
void	parse_token_string(char **str);
t_token	*init_token(char *str, enum e_ttype type);

//free
void	free_array(char **arr);
void	free_token(void);

//UTILS
int ft_strlen_double(char **str);
int ft_execute_cmds(char **cmd, char **env);
char *ft_strcat(char *s1, char *s2);
void ft_free_array_char(char **arr, int size);
void ft_free_array_int(int **arr, int size);
int	is_whitespace(char c);
int	contain_heredoc(t_process *process);
int	ft_strcmp(char *s1, char *s2);

//redirect
void	input(char *file);
void	output(char *file, int mode);
void	fill_all_heredoc(void);
void	get_all_inputs(t_process *process);
void	set_all_outputs(t_process *process);
void	heredoc(int *fd, char *endline);

//utils
int	is_operator(char *str);
int	is_parent(void);


//ENV
//set_env
// char **ft_set_env(char **envp, int size);
char **ft_set_env(char **envp, int new_size, int old_size);
void	set_env(char **env);
void	set_paths(void);
char    *get_env(char *str);
char	*get_path(char *cmd);
//env
void ft_env(t_minishell *mini);

//PIPES
void ft_pipes(t_minishell *mini);
void ft_close(t_pipes *pipes, int i);
void ft_dup2(t_pipes *pipes, t_minishell *mini, int i);
void set_pipes(t_pipes *pipes, t_minishell *mini, int set);
void ft_perror(char *error);

//BUILTIN
//builtin
void ft_builtin(t_minishell *mini);
int is_builtin(char *command);
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
int	ft_export_output(t_builtin *built, char *cmd);
//cd_pwd
void ft_cd(t_minishell *mini);
void ft_pwd(t_minishell *mini);
//export
void ft_export(t_minishell *mini);
void ft_sort_export(t_builtin *built);
void ft_swap(char **s1, char **s2);
//export_utils
int ft_add_export(t_builtin *built);
int	ft_old_var(t_builtin *built, int index, int cmd);
void	ft_export_var(t_builtin *built, int i);
int	ft_export_check(t_builtin *built, int cmd);
//unset
void ft_unset(t_minishell *mini);
void ft_unset_update(t_builtin *built, int index);
//exit
void ft_exit(t_minishell *mini);
//utils
int	ft_strcmp (char *s1, char *s2);
int	ft_cmdcmp(char *s1, char *s2);
char *ft_charcat(char *s, char c);
char *ft_strdup2(char *str, char *cmd);
int	ft_isalnum(int c);

#endif