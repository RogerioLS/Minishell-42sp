/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:13:17 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/09/29 19:08:48 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_print_args(char **args, bool has_n)
{
	if (has_n)
	{
		while (*args)
		{
			ft_putstr_fd(*args, STDOUT_FILENO);
			if (*(args + 1))
				ft_putchar_fd(' ', STDOUT_FILENO);
			args++;
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

int	ft_echo(t_token *tokens)
{
	char	**args;
	bool	has_n;

	has_n = 0;
	args = ft_get_cmd_and_args(tokens);
	args++;
	while (*args && ft_strncmp(*args, "-n", 2) == 0)
	{
		has_n = 1;
		args++;
	}
	ft_print_args(args, has_n);
	return (SUCCESS);
}
