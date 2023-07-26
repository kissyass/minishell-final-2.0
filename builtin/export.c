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
    printf("before copy\n");
    built.env = malloc(sizeof(char *) * mini->env_size);
    if (!built.env)
        return ;
    built.env_size = mini->env_size;
    while (mini->env[++i])
        built.env[i] = ft_strdup(mini->env[i]);
    printf("after copy\n");
    if (!mini->cmd[1])
    {
        printf("before sort\n");
        ft_sort_export(&built);
        printf("after sort\n");
        i = -1;
        while (built.env[++i])
            printf("declare -x %s\n", built.env[i]);
    }
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
            if (built->env[i][0] >= built->env[j][0])
                ft_swap(&built->env[i], &built->env[j]);
            else
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