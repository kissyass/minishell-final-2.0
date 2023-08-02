/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:18:34 by ykissiko          #+#    #+#             */
/*   Updated: 2023/08/02 16:18:35 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_exit(t_minishell *mini)
{
    ft_free_array_char(mini->env, mini->env_size);
    ft_free_array_char(mini->cmd, ft_strlen_double(mini->cmd));
    free(mini->input);
    printf("exit\n");
	exit(1);
}