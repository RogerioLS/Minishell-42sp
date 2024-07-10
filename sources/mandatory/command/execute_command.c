/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:48:42 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/16 14:32:08 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

void	print_environment(void)
{
	extern char	**environ;
	char		**env;

	env = environ;
	while (*env != NULL)
	{
		ft_printf("%s\n", *env);
		env++;
	}
}

int	handle_redirection(char **tokens, int *input_fd, int *output_fd, int i)
{
	if (tokens[i + 1] == NULL)
	{
		printf("syntax error near unexpected token 'newline'\n");
		return (-1);
	}
	if (strcmp(tokens[i], ">") == 0)
		*output_fd = open(tokens[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (strcmp(tokens[i], ">>") == 0)
		*output_fd = open(tokens[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (strcmp(tokens[i], "<") == 0)
		*input_fd = open(tokens[i + 1], O_RDONLY);
	if (*output_fd < 0 || *input_fd < 0)
	{
		perror("open failed");
		return (-1);
	}
	tokens[i] = NULL;
	tokens[i + 1] = NULL;
	return (0);
}

void	handle_heredoc(t_token *tokens, int *input_fd, int i)
{
	t_token	*current;
	t_token	*delimiter_token;
	char	*delimiter;
	char	*line;
	int		file_fd;
	int		j;

	current = tokens;
	delimiter_token = NULL;
	delimiter = NULL;
	line = NULL;
	j = 0;
	while (current != NULL && j <= i + 1)
	{
		if (j == i + 1)
			delimiter_token = current;
		current = current->next;
		j++;
	}
	if (delimiter_token == NULL || delimiter_token->text == NULL)
	{
		fprintf(stderr, "syntax error near unexpected token 'newline'\n");
		return ;
	}
	delimiter = delimiter_token->text;
	file_fd = open("/tmp/heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (file_fd < 0)
	{
		perror("open");
		return ;
	}
	printf("> ");
	while ((line = readline(NULL)) != NULL)
	{
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(file_fd, line, strlen(line));
		write(file_fd, "\n", 1);
		free(line);
		printf("> ");
	}
	close(file_fd);
	*input_fd = open("/tmp/heredoc.tmp", O_RDONLY);
	if (*input_fd < 0)
	{
		perror("open");
		return ;
	}
}


void	handle_redirection_and_execution(t_token *tokens)
{
	execute_command(tokens);
}


/*
void	handle_redirection_and_execution(t_token *tokens, int input_fd, int output_fd)
{
	t_token	*current;
	int		i;

	current = tokens;
	i = 0;
	while (current != NULL)
	{
		if (strcmp(current->text, "<<") == 0)
		{
			handle_heredoc(current, &input_fd, i);
			if (input_fd == -1)
				return ;
		}
		current = current->next;
		i++;
	}
	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 input_fd");
			exit(EXIT_FAILURE);
		}
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output_fd");
			exit(EXIT_FAILURE);
		}
		close(output_fd);
	}
	execute_command(current);
}
*/