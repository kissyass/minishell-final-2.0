/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeroglu <aeroglu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:47:50 by aeroglu           #+#    #+#             */
/*   Updated: 2023/07/26 20:50:18 by aeroglu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	contain_heredoc(t_process *process)
{
	int	i;

	i = 0;
	while (process->redirects[i])
	{
		if (is_operator(process->redirects[i] == HERE_DOC))
			return (TRUE);
		i++;
	}
	return (FALSE);
}