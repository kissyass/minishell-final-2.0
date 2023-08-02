/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykissiko <ykissiko@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:11:12 by ykissiko          #+#    #+#             */
/*   Updated: 2023/08/02 16:11:13 by ykissiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_env(t_minishell *mini)
{
    int i;

    i = -1;
    while (++i < mini->envp_size)
        printf("%s\n", mini->envp[i]);
}
