/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:15:53 by codespace         #+#    #+#             */
/*   Updated: 2024/08/29 01:26:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

char	***ft_get_my_env(void)
{
	static char	**env;

	return (&env);
}

int	*ft_get_exit_status(void)
{
	static int	exit_status;

	return (&exit_status);
}

int	ft_set_exit_status(int status)
{
	int	*exit_status;

	exit_status = ft_get_exit_status();
	*exit_status = status;
	return (*exit_status);
}
