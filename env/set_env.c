#include "../minishell.h"

char **ft_set_env(char **envp, int size)
{
    char **env;
    int i;

    env = malloc(sizeof(char *) * size);
    if (!env)
        return (NULL);
    i = -1;
    while (envp[++i])
        env[i] = ft_strdup(envp[i]);
    i--;
    while (++i < size)
        env[i] = NULL;
    return(env);
}