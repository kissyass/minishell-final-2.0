#include "../minishell.h"

void ft_echo(t_minishell *mini)
{
    t_builtin built;
    int i;

    i = 0;
    if (ft_strcmp(mini->cmd[1], "-n"))
        i = 1;
    built.input = malloc(sizeof(char));
    built.output = malloc(sizeof(char));
    if (!built.output || !built.input)
        return ;
    while (mini->cmd[++i + 1])
    {
        built.input = ft_strcat(built.input, mini->cmd[i]);
        built.input = ft_strcat(built.input, " ");
    }
    built.input = ft_strcat(built.input, mini->cmd[i]);
    if (!ft_check_input(&built))
    {
        free(built.input);
        return ;
    }
    printf("%s\n\n", built.input);
    printf("%s\n\n", built.output);
}

int ft_check_input(t_builtin *built)
{
    int i;

    i = -1;
    while (built->input[++i])
    {
        ft_quote(built, 0, 0);
        if (built->input[i] == '\'')
        {
            //printf("first quote\n");
            i = ft_check_quotes(built, i + 1, '\'');
            if (built->quote == 1)
            {
                printf("minishell: syntax error with open quotes\n");
                return (0);
            }
        }
        else if (built->input[i] == '"')
        {
            //printf("second quote\n");
            i = ft_check_quotes(built, i + 1, '"');
            //printf("back\n");
            if (built->dquote == 1)
            {
                printf("minishell: syntax error with open quotes\n");
                return (0);
            }
        }
        else
        {
            if ()
        }
            built->output = ft_charcat(built->output, built->input[i]);
    }
    return (1);
}

int ft_check_quotes(t_builtin *built, int index, char quote)
{
    int i;
    int backslash;

    built->start = index;
    while (built->input[index] && built->input[index] != quote)
        index++;
    //printf("inside %c\n", built->input[index]);
    i = index;
    backslash = 0;
    if (built->input[index] == quote)
    {
        //printf("backslash\n");
        while (built->input[--i] == '\\')
            backslash++;
        if (backslash > 0 && backslash % 2 == 1 && (index + 1) != ft_strlen(built->input))
            index = ft_check_quotes(built, index + 1, quote);
        else if (backslash > 0 && backslash % 2 == 1 && (index + 1) == ft_strlen(built->input))
            ft_quote(built, quote, 1);
    }
    if (!built->input[index])
        ft_quote(built, quote, 1);
    built->end = index;
    if (built->dquote == 0 && built->quote == 0)
        ft_output(built, quote);
    return (index);
}

void ft_output(t_builtin *built, char quote)
{
    int i;
    int backslash;

    //printf("in output\n");
    i = built->start - 1;
    while (++i < built->end)
    {
        //printf("here 1.0 %c\n", built->input[i]);
        if (built->input[i] != '\\')
            built->output = ft_charcat(built->output, built->input[i]);
        else
        {
            backslash = 1;
            while (++i < built->end && built->input[i] == '\\')
                backslash++;
            if (built->input[i] == quote && backslash == 1) //add special signs check
                built->output = ft_charcat(built->output, built->input[i]);
            else if (built->input[i] == quote)
                backslash--;
            if (backslash % 4 == 0)
                backslash = backslash / 4;
            else
                backslash = backslash / 4 + 1;
            while (--backslash >= 0)
                built->output = ft_charcat(built->output, '\\');
        }
    }
    
}

char *ft_charcat(char *s, char c)
{
    int i;
    char *str;

    //printf("charstrc cat %c\n", c);
    i = 0;
    if (s)
        i = ft_strlen(s);
        //printf("%d\n", i);
    //printf("charstrc cat %c\n", c);
    str = malloc(sizeof(char) * (i + 2));
    if (!str)
        return (NULL);
    if (s)
    {
        i = -1;
        while (s[++i])
            str[i] = s[i];
    }
    //printf("charstrc cat %c\n", c);
    str[i] = c;
    str[i + 1] = 0;
    //printf("str %s\n", str);
    return (str);
}

void ft_quote(t_builtin *built, char quote, int type)
{
    if (type == 0)
    {
        built->quote = 0;
        built->dquote = 0;
    }
    if (type == 1)
    {
        if (quote == '\'')
            built->quote = 1;
        else
            built->dquote = 1;
    }
}