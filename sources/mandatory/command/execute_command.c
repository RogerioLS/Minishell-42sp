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

int	handle_redirection(char **tokens, int *input_fd, \
						int *output_fd, int i)
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

int	handle_heredoc(char **tokens, int i)
{
	char	*delimiter;
	char	*line;
	size_t	bufsize;
	ssize_t	chars_read;

	delimiter = tokens[i + 1];
	if (delimiter == NULL)
	{
		printf("syntax error near unexpected token 'newline'\n");
		return (-1);
	}
	tokens[i] = NULL;
	tokens[i + 1] = NULL;
	line = NULL;
	bufsize = 0;
	chars_read = getline(&line, &bufsize, stdin);
	while (chars_read != -1)
	{
		if (strcmp(line, delimiter) == 0)
			break ;
	}
	free(line);
	return (0);
}

void handle_redirection_and_execution(t_token *tokens)
{
	execute_command(tokens);
}


/*void	handle_redirection_and_execution(char **tokens, int input_fd, int output_fd)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (strcmp(tokens[i], ">") == 0 || \
		strcmp(tokens[i], ">>") == 0 || strcmp(tokens[i], "<") == 0)
		{
			if (handle_redirection(tokens, &input_fd, &output_fd, i) == -1)
				return ;
		}
		else if (strcmp(tokens[i], "<<") == 0)
		{
			if (handle_heredoc(tokens, i) == -1)
				return ;
		}
		i++;
	}
	execute_command(tokens);
}*/
