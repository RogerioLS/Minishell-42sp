/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:06:46 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/09/13 19:06:26 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_close_pipe(int *pipe_fd)
{
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
}

int	ft_set_exit_status(int status)
{
	int	*exit_status;

	exit_status = ft_get_exit_status();
	*exit_status = status;
	return (*exit_status);
}

int	*ft_get_exit_status(void)
{
	static int	exit_status;

	return (&exit_status);
}
