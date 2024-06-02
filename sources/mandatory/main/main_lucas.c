/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lucas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:27:05 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/02 14:18:47 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

void	print_tokens(t_token *head)
{
	while (head != NULL)
	{
		ft_printf("Recebido: %s \nToken de tipo: %d\n\n", head->text,
			head->type);
		head = head->next;
	}
}

char	*expandVariables(const char *input)
{
	char		*buffer;
	const char	*cursor;
	size_t		current_length;
	size_t		name_length;
	char		*name;
	char		*value;

	buffer = malloc(strlen(input) + 1);
	if (!buffer)
	{
		perror("malloc failed");
		return (NULL);
	}
	buffer[0] = '\0';
	cursor = input;
	current_length = 0;
	while (*cursor)
	{
		if (*cursor == '$')
		{
			cursor++;
			if (*cursor == '$')
			{
				buffer = realloc(buffer, current_length + 2);
				if (!buffer)
				{
					perror("realloc failed");
					return (NULL);
				}
				buffer[current_length++] = '$';
				buffer[current_length] = '\0';
				cursor++;
			}
			else if (*cursor == '?')
			{
				buffer = realloc(buffer, current_length + 2);
				if (!buffer)
				{
					perror("realloc failed");
					return (NULL);
				}
				buffer[current_length++] = '0';
				buffer[current_length] = '\0';
				cursor++;
			}
			else
			{
				name_length = strcspn(cursor, " $/\t\n,.'\"");
				name = malloc(name_length + 1);
				if (!name)
				{
					perror("malloc failed");
					free(buffer);
					return (NULL);
				}
				strncpy(name, cursor, name_length);
				name[name_length] = '\0';
				value = getenv(name);
				free(name);
				if (value)
				{
					buffer = realloc(buffer, current_length + strlen(value)
						+ 1);
					if (!buffer)
					{
						perror("realloc failed");
						return (NULL);
					}
					strcat(buffer, value);
					current_length += strlen(value);
				}
				cursor += name_length;
			}
		}
		else
		{
			buffer = realloc(buffer, current_length + 2);
			if (!buffer)
			{
				perror("realloc failed");
				return (NULL);
			}
			buffer[current_length++] = *cursor++;
			buffer[current_length] = '\0';
		}
	}
	return (buffer);
}

int	main(void)
{
	t_mini	mini;
	t_token	*tokens;
	char	**args;

	initialize_shell();
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, handle_signal);
	while (1)
	{
		mini.cmd_line = read_command();
		if (!mini.cmd_line)
		{
			ft_printf("\n");
			exit(EXIT_SUCCESS);
		}
		if (*mini.cmd_line)
		{
			add_history(mini.cmd_line);
			tokens = input_tokenizer(mini.cmd_line);
			if (tokens)
			{
				args = tokens_to_argv(tokens);
				handle_redirection_and_execution(args, STDIN_FILENO,
					STDOUT_FILENO);
				ft_free_string_array(args);
			}
			else
			{
				ft_printf("Failed to split command line\n");
			}
		}
		free(mini.cmd_line);
	}
	return (0);
}
