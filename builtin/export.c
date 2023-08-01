/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 17:23:31 by ykissiko          #+#    #+#             */
/*   Updated: 2023/07/25 17:23:32 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_export(t_minishell *mini)
{
    printf("inside export\n");
    int i;
    t_builtin built;

    i = -1;
    //built.env = malloc(sizeof(char *) * mini->env_size);
    built.input = malloc(sizeof(char));
    if (!built.input)
        return ;
    printf("0\n");
    built.env_size = mini->env_size;
    // while (mini->env[++i])
    //     built.env[i] = ft_strdup(mini->env[i]);
    built.env = ft_set_env(mini->env, mini->env_size);
    printf("1\n");
    if (!mini->cmd[1])
    {
        printf("2\n");
        ft_sort_export(&built);
        i = -1;
        printf("2.1\n");
        while (built.env[++i])
            printf("declare -x %s\n", built.env[i]);
        printf("2.2\n");
    }
    else
    {
        printf("3\n");
        built.input = ft_strdup2(mini->input, "export");
        printf("%s\n", built.input);
        printf("4\n");
        ft_add_export(&built);
        printf("5\n");
        mini->env = ft_set_env(built.env, built.env_size);
        printf("mini %d, built %d\n", mini->env_size, built.env_size);
        mini->env_size = built.env_size;
    }
}

int ft_add_export(t_builtin *built)
{
    printf("in ft add export\n");
    int i;
    char *var;

    i = -1;
    printf("add 1\n");
    ft_quote(built, 0, 0);
    printf("add 2\n");

    built->end = 0;
    built->output = malloc(sizeof(char));
    var = malloc(sizeof(char));
    if (!built->output || !var)
        return (0);
    if (!built->input[0] || (built->input[0] >= '0' && built->input[0] <= '9'))
        return(printf("export: '%s': not a valid identifier\n", built->input));
    printf("add 3\n");
    while (built->input[++i])
    {
    printf("add 4\n");
        if (built->input[i] == '"' || built->input[i] == '\'')
        {
            i++;
            built->end = ft_check_quotes(built, i, built->input[i]);
            if (built->quote == 1 || built->dquote == 1)
                return(printf("Minishell: syntax error with open quotes\n"));
            i--;
            while (++i < built->end)
                built->output = ft_charcat(built->output, built->input[i]);
            i++;
        }
        if (!built->input[i] || built->input[i] == ' ')
            break;
        else
            built->output = ft_charcat(built->output, built->input[i]);
    }
    printf("add 5\n");

    i = -1;
    while (built->output[++i] && built->output[i] != '=')
    {
    printf("add 6\n");

        if (ft_isalnum(built->output[i]))
            var = ft_charcat(var, built->output[i]);
        else
            return(printf("export: '%s': not a valid identifier\n", built->output));
    }
    printf("add 7\n");

    if (built->output[i])
    {
    printf("add 8\n");

        var = ft_charcat(var, built->output[i]);
        var = ft_charcat(var, '"');
        while (built->output[++i])
            var = ft_charcat(var, built->output[i]);
        var = ft_charcat(var, '"');
    }
    printf("add 9\n");
    built->env = ft_set_env(built->env, built->env_size + 1);
    printf("add 10\n");

    built->env_size++;
    built->env[built->env_size - 1] = ft_strdup(var);
    printf("add 11\n");
    printf("var %s\nbuilt.env = %s\nsize %d\n", var, built->env[built->env_size - 1], built->env_size);
    printf("add 12\n");

        

    // while (built->input[++i] && built->input[i] != '=')
    // {
    //     if ((built->input[i] == '"' || built->input[i] == '\'') && built->end >= i)
    //     {
    //         i++;
    //         built->end = ft_check_quotes(built, i, built->input[i]);
    //     }
    //     if (built->quote == 1 || built->dquote == 1)
    //         return(printf("Minishell: syntax error with open quotes\n"));
    //     if (ft_isalnum(built->input[i]))
    //         built->output = ft_charcat(built->output, built->input[i]);
    //     else
    //         return(printf("export: '%s': not a valid identifier\n", built->input));
    // }
    // built->output = ft_charcat(built->output, built->input[i]);
    // built->output = ft_charcat(built->output, '"');
    // while (built->input[++i])
    // {
    //     if ((built->input[i] == '"' || built->input[i] == '\'') && built->end >= i)
    //     {
    //         i++;
    //         built->end = ft_check_quotes(built, i, built->input[i]);
    //     }
    //     if (built->input[i] == ' ')
    //     {
    //         if (i < built->end && (built->input[built->end] == '"' || built->input[built->end] == '\''))
    //             built->output = ft_charcat(built->output, built->input[i]);
    //         else
    //         {
    //             built->output = ft_charcat(built->output, '"');
    //             break ;
    //         }
    //     }
    //     else
    //         built->output = ft_charcat(built->output, built->input[i]);
    // }

    printf("%s", built->output);
    return(printf("still in progress\n"));
}

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z') || c == '_' || c == '"' || c == '\'' || c == '\\')
		return (1);
	return (0);
}

int ft_check_name(char *name)
{
    int i;

    i = 0;
	while (name[++i])
	{
		if (!ft_isalnum(name[i]))
            return(printf("Wrong name\n"));
		if (i == 0)
		{
			if (name[i] >= '0' && name[i] <= '9')
				return(printf("Wrong name\n"));
		}
	}
	return (1);
}

int ft_check_export(char c)
{
    if (c == '=')
        return (1);
    else if (c == '\'')
        return (2);
    else if (c == '"')
        return (3);
    else if (c == ' ')
        return (4);
    else if (c == '\\')
        return (5);
    else
        return(0);
}

void ft_sort_export(t_builtin *built)
{
    int i;
    int j;
    int k;

    i = -1;
    printf("in sort\n");
    // while (built->env[++i])
    while (++i < built->env_size)
    {
        j = i;
        // if (!built->env[i][1])
        //     ft_swap(&built->env[i], &built->env[built->env_size - 1]);
        // while (built->env[++j])
        while (++j < built->env_size)
        {
        printf("i = %d, j = %d, env[i] = %s, env[j] = %s\n", i, j, built->env[i], built->env[j]);
            k = 1;
            if (built->env[i][0] > built->env[j][0])
                ft_swap(&built->env[i], &built->env[j]);
            else if (built->env[i][0] == built->env[j][0])
            {
                while (built->env[i][k] == built->env[j][k])
                    k++;
                if (built->env[i][k] > built->env[j][k])
                    ft_swap(&built->env[i], &built->env[j]);
            }
        }
    }

}

void ft_swap(char **s1, char **s2)
{
	char **temp;

	temp = malloc(sizeof(char *) * (ft_strlen(*s1) + 1));
	if (!temp)
		return;
	*temp = *s1;
	*s1 = *s2;
	*s2 = *temp;
	free(temp);
}