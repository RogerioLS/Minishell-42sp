/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:48:42 by roglopes          #+#    #+#             */
/*   Updated: 2024/05/05 17:21:43 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

size_t	ft_arraylen(char **array)
{
	size_t	len;

	len = 0;
	while (array[len] != NULL)
	{
		len++;
	}
	return (len);
}

// Forbidden structure
void	print_environment(void)
{
	extern char	**environ;

	for (char **env = environ; *env != NULL; env++)
	{
		ft_printf("%s\n", *env);
	}
}

void	execute_command(char **args, int argc)
{
	if (args == NULL || args[0] == NULL)
	{
		return ;
	}
	if (ft_strcmp(args[0], "pwd") == 0)
	{
		ft_pwd(argc - 1, args + 1);
	}
	else if (ft_strcmp(args[0], "ls") == 0)
	{
		list_directory(args);
	}
	else if (ft_strcmp(args[0], "clear") == 0)
	{
		clear_screen();
	}
	else if (ft_strcmp(args[0], "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if (ft_strcmp(args[0], "cd") == 0)
	{
		ft_cd(args[1]);
	}
	else if (ft_strcmp(args[0], "export") == 0)
	{
		export_variable(args);
	}
	else if (ft_strcmp(args[0], "env") == 0)
	{
		print_environment();
	}
	else
	{
		ft_printf("command not found: %s\n", args[0]);
	}
}
