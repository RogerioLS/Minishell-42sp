/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:59:07 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/16 14:01:30 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

int	count_commands(char ***commands)
{
	int	count;

	count = 0;
	while (commands[count] != NULL)
		count++;
	return (count);
}

void	create_pipes(int *pipefds, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipefds + i * 2) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	close_pipes(int *pipefds, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes * 2)
	{
		close(pipefds[i]);
		i++;
	}
}

void	setup_redirection(int *pipefds, int num_pipes, int i)
{
	if (i > 0)
	{
		if (dup2(pipefds[(i - 1) * 2], 0) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	if (i < num_pipes)
	{
		if (dup2(pipefds[i * 2 + 1], 1) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
}

void	execute_command_in_pipeline(char **command, int *pipefds, int num_pipes,
		int i)
{
	setup_redirection(pipefds, num_pipes, i);
	close_pipes(pipefds, num_pipes);
	execvp(command[0], command);
	perror("execvp");
	exit(EXIT_FAILURE);
}
