#include "../minishell.h"

int	ft_strcmp (char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if ((!s1 && !s2))
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}