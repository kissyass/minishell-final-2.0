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
    //printf("inside export\n");
    int i;
    t_builtin built;

    i = -1;
    built.env = malloc(sizeof(char *) * mini->env_size);
    built.input = malloc(sizeof(char));
    if (!built.env || !built.input)
        return ;
    built.env_size = mini->env_size;
    while (mini->env[++i])
        built.env[i] = ft_strdup(mini->env[i]);
    if (!mini->cmd[1])
    {
        ft_sort_export(&built);
        i = -1;
        while (built.env[++i])
            printf("declare -x %s\n", built.env[i]);
    }
    else
    {
        built.input = ft_strdup2(mini->input, "export");
        ft_add_export(&built);
    }
}

int ft_add_export(t_builtin *built)
{
    int i;

    i = -1;
    built->output = malloc(sizeof(char));
    if (!built->output)
        return (0);
    while (built->input[++i] && ft_check_export(built->input[i]) == 0)
        built->output = ft_charcat(built->output, built->input[i]);
    if (ft_check_export(built->input[i]) == 4)
        return(printf("export: not valid in this context: %s\n", built->output));
    else if (ft_check_export(built->input[i]) == 5)
        return(printf("zsh: bad assignment\n"));
    else if (ft_check_export(built->input[i]) == 1)
    {
        if (ft_check_name(built->output) != 1)
            return (0);
    }
    return(printf("still in progress\n"));
}

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z') || c == '_' || c == '"' || c == '\'' || c =='=')
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
    while (built->env[++i])
    {
        j = i;
        // if (!built->env[i][1])
        //     ft_swap(&built->env[i], &built->env[built->env_size - 1]);
        while (built->env[++j])
        {
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