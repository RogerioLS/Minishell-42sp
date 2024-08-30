/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:13:17 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/30 15:25:53 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	ft_echo(t_token *tokens)
{
	char	**args;
	bool	has_n;

	has_n = true;
	args = get_cmd_and_args(tokens);
	args++;
	while (*args && ft_strncmp(args, "-n", 2) == 0)
	{
		has_n = false;
		args++;
	}
	ft_print_args(args, has_n);
	return (SUCCESS);
}

void	ft_print_args(char **args, bool has_n)
{
	while (*args)
	{
		ft_putstr_fd(*args, STDOUT_FILENO);
		if (*(args + 1))
			ft_putchar_fd(' ', STDOUT_FILENO);
		args++;
	}
	if (!has_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
