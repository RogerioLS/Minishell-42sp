/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 00:34:57 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/08/29 13:59:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

void	ft_free_env(int i)
{
	char	**env;

	env = *ft_get_my_env();
	while (env[i++])
		free(env[i]);
	free(env);
}

void	ft_free_memory(void)
{
	ft_lstclear(ft_get_memory_lst(), &free);
}
