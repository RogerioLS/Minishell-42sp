/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:53:37 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/16 16:10:55 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

char	***parse_commands_with_pipes(char **args)
{
	int		num_pipes;
	char	***commands;

	num_pipes = count_pipes(args);
	commands = allocate_commands(num_pipes);
	split_commands(args, commands);
	return (commands);
}

int	count_pipes(char **args)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (args[i])
	{
		if (strcmp(args[i], "|") == 0)
			count++;
		i++;
	}
	return (count);
}

char	***allocate_commands(int num_pipes)
{
	char	***commands;

	commands = malloc((num_pipes + 2) * sizeof(char **));
	if (!commands)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (commands);
}

void	split_commands(char **args, char ***commands)
{
	int	i;
	int	cmd_idx;

	i = 0;
	cmd_idx = 0;
	commands[cmd_idx] = args;
	while (args[i])
	{
		if (strcmp(args[i], "|") == 0)
		{
			args[i] = NULL;
			commands[++cmd_idx] = &args[i + 1];
		}
		i++;
	}
	commands[cmd_idx + 1] = NULL;
}

void	execute_pipeline(char ***commands)
{
	int		num_commands;
	int		i;
	pid_t	pid;
	int		*pipefds;

	num_commands = count_commands(commands);
	pipefds = malloc(2 * (num_commands - 1) * sizeof(int));
	ft_valid_malloc(pipefds);
	create_pipes(pipefds, num_commands - 1);
	i = 0;
	while (i < num_commands)
	{
		pid = fork();
		if (pid == 0)
			execute_command_in_pipeline(commands[i], pipefds, num_commands - 1,
				i);
		i++;
	}
	close_pipes(pipefds, num_commands - 1);
	i = 0;
	while (i < num_commands)
	{
		wait(NULL);
		i++;
	}
}
