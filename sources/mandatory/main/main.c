/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:27:05 by roglopes          #+#    #+#             */
/*   Updated: 2024/05/19 18:39:41 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

void	print_tokens(t_token *head)
{
	while (head != NULL)
	{
		ft_printf("Recebido: %s \nToken de tipo: %d\n\n", head->text, head->type);
		head = head->next;
	}
}

char	*expandVariables(const char *input)
{
	char		*buffer;
	const char	*cursor;
	size_t		name_length;
	char		*name;
	char		*valeu;
	size_t		current_length;

	buffer = malloc(ft_strlen(input) + 1);
	if (!buffer)
	{
		perror("malloc failed");
		return (NULL);
	}
	buffer[0] = '\0';
	cursor = input;
	while (*cursor)
	{
		if (*cursor == '$')
		{
			cursor++;
			name_length = strcspn(cursor, " $/\t\n,.");
			name = malloc(name_length + 1);
			if (!name)
			{
				perror("malloc failed");
				free(buffer);
				return (NULL);
			}
			strncpy(name, cursor, name_length);
			name[name_length] = '\0';
			valeu = getenv(name);
			free(name);
			if (valeu)
			{
				buffer = realloc(buffer, strlen(buffer) + strlen(valeu) + 1);
				if (!buffer)
				{
					perror("realloc failed");
					return (NULL);
				}
				strcat(buffer, valeu);
			}
			cursor += name_length;
		}
		else
		{
			current_length = strlen(buffer);
			buffer = realloc(buffer, current_length + 2);
			if (!buffer)
			{
				perror("realloc failed");
				return (NULL);
			}
			buffer[current_length] = *cursor++;
			buffer[current_length + 1] = '\0';
		}
	}
	return (buffer);
}

//e_token_type
int	main(void)
{
	t_mini	mini;
	t_token	*tokens;
	char	**parce;
	char	*expanded;

	ft_printf("\033[1;33mMINIHELL started!\033[0m\n");
	// lembrar de pegar prioridade do terminal com term_ios.h
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, handle_signal);
	while (1)
	{
		mini.cmd_line = prompt();
		if (!mini.cmd_line)
		{
			ft_printf("\n");
			exit(EXIT_SUCCESS);
		}
		if (mini.cmd_line && *mini.cmd_line)
		{
			tokens = input_tokenizer(mini.cmd_line);
			parce = tokens_to_argv(tokens);
			expanded = expandVariables(*parce);
			ft_printf("aqui %s \n", expanded);
			//execute_command(parce, ft_arraylen(tokens_parce), STDIN_FILENO, STDOUT_FILENO);
			print_tokens(tokens);
			ft_free_tokens(tokens);
			free(parce);
		}
		free(mini.cmd_line);
	}
	return (0);
}
