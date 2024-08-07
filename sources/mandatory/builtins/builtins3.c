/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:17:06 by codespace         #+#    #+#             */
/*   Updated: 2024/07/30 01:41:59 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

static int	echo_env(char *content, t_data *data)
{
	char	**split;
	int		status;

	split = ft_split(content, ' ');
	if (split[1])
		status = ft_echo(split, data);
	else
		status = 0;
	free_trash(split);
	return (status);
}

static int	check_multi_n(char *str)
{
	int	i;

	if (str[0] != '-')
		return (1);
	i = 1;
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

int	ft_echo(char **arg, t_data *data)
{
	int	index;

	if (ft_strncmp(arg[0], "echo", 5) == 0 && arg[1] != NULL)
	{
		if (check_multi_n(arg[1]) == 0)
			index = 2;
		else
			index = 1;
		while (arg[index])
		{
			if (ft_strncmp(arg[index], "\"\"", 3) == 0)
				index++;
			else if (arg[index] != NULL)
				ft_putstr_fd(arg[index++], 1);
			if (arg[index] != NULL)
				ft_putchar_fd(' ', 1);
		}
		if (ft_strncmp(arg[1], "-n", 3) != 0)
			ft_putchar_fd('\n', 1);
		return (1);
	}
	else if (data->has_env == TRUE)
		return (echo_env(arg[0], data));
	return (0);
}
