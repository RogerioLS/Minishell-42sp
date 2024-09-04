/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 00:34:57 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/09/04 19:33:22 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

void	ft_free_env(void)
{
	int		i;
	char	**env;

	i = -1;
	env = *ft_get_my_env();
	while (env[++i])
		free(env[i]);
	free(env);
}

void	ft_free_memory(void)
{
	ft_lstclear(ft_get_memory_lst(), &free);
}
