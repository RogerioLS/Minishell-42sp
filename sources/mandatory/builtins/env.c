/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:29:03 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/30 15:57:51 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	ft_env(t_token *cmd)
{
	int		i;
	char	**env;

	env = *get_my_env();
	if (cmd->next)
		return (!!write(STDERR_FILENO, "env: too many arguments\n", 24));
	i = 0;
	while (env[i])
	{
		ft_putstr_fd(env[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (SUCCESS);
}

char	***get_my_env(void)
{
	static char	**env;

	return (&env);
}
