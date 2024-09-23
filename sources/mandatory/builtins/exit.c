/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:00:56 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/09/23 19:18:18 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	check_limits(char *arg, char sign)
{
	if (*arg == '+' || *arg == '-')
		arg++;
	if (ft_strlen(arg) > 19)
		return (FAILURE);
	if ((ft_strcmp(arg, "9223372036854775807") > 0 && sign == '+')
		|| (ft_strcmp(arg, "9223372036854775808") > 0 && sign == '-'))
		return (FAILURE);
	return (SUCCESS);
}

int	validate_argument(char *arg)
{
	int		i;
	char	sign;

	i = 0;
	sign = '+';
	if (arg[i] == '-' || arg[i] == '+')
	{
		sign = arg[i];
		i++;
	}
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (FAILURE);
		i++;
	}
	if (check_limits(arg, sign) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	status_ft(int status)
{
	delete_heredoc_files();
	ft_free_memory();
	if (status)
		exit(status % 256);
}

int	ft_exit(t_token *tokens)
{
	long	status;

	status = 0;
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		printf("exit\n");
	if (tokens->next)
	{
		status = ft_atol(tokens->next->value);
		if (validate_argument(tokens->next->value) || \
				*(tokens->next->value) == '\0')
		{
			ft_fprintf(STDERR_FILENO, "exit:%s: numeric argument required\n", \
			tokens->next->value);
			exit(SYNTAX_ERROR);
		}
		if (tokens->next->next)
		{
			write(STDERR_FILENO, "exit: too many arguments\n", 25);
			exit(FAILURE);
		}
	}
	status_ft(status);
	exit(*ft_get_exit_status());
}
