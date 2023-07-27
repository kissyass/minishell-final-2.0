/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeroglu <aeroglu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:32:15 by aeroglu           #+#    #+#             */
/*   Updated: 2023/07/27 21:19:49 by aeroglu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char *arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_token(void)
{
	t_token	*tmp;
	t_token	*token;

	token = g_ms.token;
	while (token)
	{
		free(token->str);
		token = token->next;
	}
	token = g_ms.token;
	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp);
	}
}