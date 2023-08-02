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

void	ft_export(t_minishell *mini)
{
	int			i;
	t_builtin	built;

	i = -1;
	built.input = malloc(sizeof(char));
	if (!built.input)
		return ;
	built.env_size = mini->env_size;
	built.env = ft_set_env(mini->env, mini->env_size, mini->env_size);
	if (!mini->cmd[1])
	{
		ft_sort_export(&built);
		i = -1;
		while (++i < built.env_size)
			printf("declare -x %s\n", built.env[i]);
	}
	else
	{
		built.input = ft_strdup2(mini->input, "export");
		ft_add_export(&built);
		mini->env = ft_set_env(built.env, built.env_size, built.env_size);
		mini->env_size = built.env_size;
        printf("mini: %s, built: %s\n", mini->env[mini->env_size - 1], built.env[built.env_size]);
	}
}

int	ft_export_output(t_builtin *built)
{
	int	i;

	i = -1;
	if (!built->input[0] || (built->input[0] >= '0' && built->input[0] <= '9'))
		return (printf("export: '%s': not a valid identifier\n", built->input));
	while (built->input[++i])
	{
		if (built->input[i] == '"' || built->input[i] == '\'')
		{
			i++;
			built->end = ft_check_quotes(built, i, built->input[i]);
			if (built->quote == 1 || built->dquote == 1)
				return (printf("Minishell: syntax error with open quotes\n"));
			i--;
			while (++i < built->end)
				built->output = ft_charcat(built->output, built->input[i]);
			i++;
		}
		if (!built->input[i] || built->input[i] == ' ')
			break ;
		else
			built->output = ft_charcat(built->output, built->input[i]);
	}
	return (0);
}

int	ft_export_check(t_builtin *built)
{
	char	*str;
    char *more;
	int		i;

	str = malloc(sizeof(char) * 1);
    more = malloc(sizeof(char) * 1);
	if (!more || !str)
		return (0);
	i = -1;
    str[0] = 0;
    printf("var before start %s\n", str);
    printf("more before start %s\n", more);
	while (built->output[++i] && built->output[i] != '=')
	{
		if (ft_isalnum(built->output[i]))
			str = ft_charcat(str, built->output[i]);
		else
			return (printf("export: '%s': not a valid identifier\n",
					built->output));
        printf("var inside: %s and i %d\n", str, i);
	}
    printf("export check var %s\n", str);
	if (!ft_old_var(built, str, i))
	{
        printf("notold\n");
        str = ft_export_var(built, str, i);
        printf("is back\n");
        printf("var not old: %s", str);
		built->env = ft_set_env(built->env, built->env_size + 1,
				built->env_size);
		built->env_size++;
		built->env[built->env_size - 1] = ft_strdup(str);
	}
    free(str);
    free(more);
	return (0);
}

char	*ft_export_var(t_builtin *built, char *var, int i)
{
    char *str;


    str = ft_strdup(var);
    printf("export var\n");
	if (built->output[i])
	{
		str = ft_charcat(str, built->output[i]);
		str = ft_charcat(str, '"');
		while (built->output[++i])
			str = ft_charcat(str, built->output[i]);
		str = ft_charcat(str, '"');
	}
    printf("var %s\n", var);
    printf("str %s\n", str);
    free(var);
	return (str);
}

int	ft_old_var(t_builtin *built, char *var, int index)
{
	int		i;
	char	**name;

    printf("old var\n");
	i = -1;
	while (++i < built->env_size)
	{
		name = ft_split(built->env[i], '=');
		if (ft_cmdcmp(name[0], var))
		{
            printf("var old: %s", var);
			var = ft_export_var(built, var, index);
			free(built->env[i]);
			built->env[i] = ft_strdup(var);
			//free(var);
            ft_free_array_char(name, ft_strlen_double(name));
			return (1);
		}
        ft_free_array_char(name, ft_strlen_double(name));
	}
    printf("no match\n");
	return (0);
}

int	ft_add_export(t_builtin *built)
{
	ft_quote(built, 0, 0);
	built->end = 0;
	built->output = malloc(sizeof(char));
	if (!built->output)
		return (0);
	if (ft_export_output(built) != 0)
		return (0);
	ft_export_check(built);
    //printf("input %s, output %s\n", built->input, built->output);
	return (0);
}

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a'
			&& c <= 'z') || c == '_' || c == '"' || c == '\'' || c == '\\')
		return (1);
	return (0);
}

int	ft_check_export(char c)
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
		return (0);
}

void	ft_sort_export(t_builtin *built)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (++i < built->env_size)
	{
		j = i;
		while (++j < built->env_size)
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

void	ft_swap(char **s1, char **s2)
{
	char **temp;

	temp = malloc(sizeof(char *) * (ft_strlen(*s1) + 1));
	if (!temp)
		return ;
	*temp = *s1;
	*s1 = *s2;
	*s2 = *temp;
	free(temp);
}