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

int	setup_redirection(t_token *tokens, int *input_fd, int *output_fd)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if (strcmp(current->text, ">") == 0 || strcmp(current->text, ">>") == 0
			|| strcmp(current->text, "<") == 0)
		{
			if (current->next == NULL)
			{
				fprintf(stderr,
					"syntax error near unexpected token 'newline'\n");
				return (-1);
			}
			if (strcmp(current->text, ">") == 0)
				*output_fd = open(current->next->text,
						O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if (strcmp(current->text, ">>") == 0)
				*output_fd = open(current->next->text,
						O_CREAT | O_WRONLY | O_APPEND, 0644);
			else if (strcmp(current->text, "<") == 0)
				*input_fd = open(current->next->text, O_RDONLY);
			if (*output_fd < 0 || *input_fd < 0)
			{
				perror("open failed");
				return (-1);
			}
			current->text = NULL;
			current->next->text = NULL;
		}
		current = current->next;
	}
	return (0);
}

/*
void	execute_command_in_pipeline(char **command, int *pipefds, int num_pipes,
		int i)
{
	setup_redirection(pipefds, num_pipes, i);
	close_pipes(pipefds, num_pipes);
	execvp(command[0], command);
	perror("execvp");
	exit(EXIT_FAILURE);
}
*/
