/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_rog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:58:49 by roglopes          #+#    #+#             */
/*   Updated: 2024/04/13 15:50:21 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../../includes/mandatory/mini_shell.h"
// A primeira etapa de processamento é a leitura do comando.
// Funcao para lidar com entrada do usuario

// para executar o nao esquece de add a flag de readline pois precisamos capturar
// entrada do usuaruio.
// gcc -o minishell main.c -lreadline
// apos a execucao digite algo.
// para finalizar o programa basta da crtl+d

#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

typedef enum
{
	TOKEN_WORD,
	TOKEN_OPERATOR,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND_OUT
}					TokenType;

typedef struct Token
{
	char			*text;
	TokenType		type;
	struct Token	*next;
}					Token;

typedef struct Alias
{
	char			*name;
	char			*command;
	struct Alias	*next;
}					Alias;

typedef enum
{
	COMMAND_SIMPLE,
	COMMAND_PIPELINE,
	COMMAND_REDIRECTION_INPUT,
	COMMAND_REDIRECTION_OUTPUT,
	COMMAND_REDIRECTION_APPEND
}					CommandType;

typedef struct Command
{
	char			*text;
	CommandType		type;
	struct Command	*next;
}					Command;

void	executeCommand(Command *cmd)
{
	char	*argv[128];
	int		argc;
	char	*token;
	pid_t	pid;
		int status;

	argc = 0;
	token = strtok(cmd->text, " ");
	while (token != NULL && argc < 127)
	{
		argv[argc++] = token;
		token = strtok(NULL, " ");
	}
	argv[argc] = NULL;
	pid = fork();
	if (pid == 0)
	{
		if (execvp(argv[0], argv) == -1)
		{
			perror("shell");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
	else
	{
		perror("fork");
	}
}

Command	*createCommand(char *text, CommandType type)
{
	Command	*cmd;

	cmd = malloc(sizeof(Command));
	if (!cmd)
		return (NULL);
	cmd->text = strdup(text);
	cmd->type = type;
	cmd->next = NULL;
	return (cmd);
}

void	appendCommand(Command **head, Command *newCmd)
{
	Command	*temp;

	if (!*head)
	{
		*head = newCmd;
	}
	else
	{
		temp = *head;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = newCmd;
	}
}

Command	*parseCommands(Token *tokens)
{
	Command	*head;
	Command	*currentCommand;
	char	commandText[1024];

	head = NULL;
	currentCommand = NULL;
	commandText[1024] = "";
	while (tokens != NULL)
	{
		switch (tokens->type)
		{
		case TOKEN_WORD:
			if (strlen(commandText) > 0)
				strcat(commandText, " ");
			strcat(commandText, tokens->text);
			break ;
		case TOKEN_PIPE:
			if (strlen(commandText) > 0)
			{
				currentCommand = createCommand(commandText, COMMAND_SIMPLE);
				appendCommand(&head, currentCommand);
				commandText[0] = '\0';
			}
			if (currentCommand != NULL)
				currentCommand->type = COMMAND_PIPELINE;
			break ;
		default:
			break ;
		}
		tokens = tokens->next;
	}
	if (strlen(commandText) > 0)
	{
		currentCommand = createCommand(commandText, COMMAND_SIMPLE);
		appendCommand(&head, currentCommand);
	}
	return (head);
}

void	freeCommands(Command *head)
{
	Command	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->text);
		free(temp);
	}
}

char	*expandVariables(const char *input)
{
	char		*buffer;
	const char	*cursor;
	char		*tempCursor;
	size_t		varNameLen;
			char varName[varNameLen + 1];
	char		*varValue;
	size_t		currentLength;

	buffer = malloc(strlen(input) + 1);
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	cursor = input;
	while (*cursor)
	{
		if (*cursor == '$')
		{
			cursor++;
			varNameLen = strcspn(cursor, " $/\t\n");
			strncpy(varName, cursor, varNameLen);
			varName[varNameLen] = '\0';
			varValue = getenv(varName);
			if (varValue)
			{
				buffer = realloc(buffer, strlen(buffer) + strlen(varValue) + 1);
				strcat(buffer, varValue);
			}
			cursor += varNameLen;
		}
		else
		{
			currentLength = strlen(buffer);
			buffer = realloc(buffer, currentLength + 2);
			tempCursor = buffer + currentLength;
			*tempCursor++ = *cursor++;
			*tempCursor = '\0';
		}
	}
	return (buffer);
}

Token	*createToken(const char *text, TokenType type)
{
	Token	*token;

	token = malloc(sizeof(Token));
	if (!token)
		return (NULL);
	token->text = strdup(text);
	token->type = type;
	token->next = NULL;
	return (token);
}

void	freeTokens(Token *head)
{
	Token	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->text);
		free(temp);
	}
}

bool	isOperatorChar(char c)
{
	return (strchr(" \t\n|&;()<>", c) != NULL);
}

Token	*tokenizeInput(char *input)
{
	Token	*head;
	Token	**current;
	char	*start;
	char	*cursor;
	bool	inQuotes;
	char	quoteType;
	char	op[2];

	head = NULL;
	current = &head;
	start = input;
	cursor = input;
	inQuotes = false;
	quoteType = 0;
	while (*cursor)
	{
		if (inQuotes)
		{
			if (*cursor == quoteType)
				inQuotes = false;
			cursor++;
		}
		else
		{
			if (*cursor == '\'' || *cursor == '\"')
			{
				inQuotes = true;
				quoteType = *cursor;
			}
			else if (isOperatorChar(*cursor) || *(cursor + 1) == '\0')
			{
				if (start < cursor)
				{
					*current = createToken(start, TOKEN_WORD);
					current = &(*current)->next;
				}
				if (isOperatorChar(*cursor))
				{
					op[2] = {*cursor, '\0'};
					*current = createToken(op, TOKEN_OPERATOR);
					current = &(*current)->next;
				}
				start = cursor + 1;
			}
			cursor++;
		}
	}
	return (head);
}

// Modificação na definição da função expandAliases
void	expandAliases(Token *tokens, Alias *aliasMap)
{
	Token	*current;
	Alias	*alias;

	current = tokens;
	while (current != NULL)
	{
		if (current->type == TOKEN_WORD)
		{
			alias = aliasMap;
			while (alias != NULL)
			{
				if (strcmp(current->text, alias->name) == 0)
				{
					free(current->text);
					current->text = strdup(alias->command);
					break ;
				}
				alias = alias->next;
			}
		}
		current = current->next;
	}
}

int	main(void)
{
	char	*input;
	Alias	*aliasMap;
	char	*expandedInput;
	Token	*tokens;
	Command	*commands;
	Command	*cmd;

	aliasMap = NULL;
	input = readline("shell> ");
	while (input != NULL)
	{
		if (strlen(input) > 0)
			add_history(input);
		expandedInput = expandVariables(input);
		free(input);
		tokens = tokenizeInput(expandedInput);
		free(expandedInput);
		expandAliases(tokens, aliasMap);
		commands = parseCommands(tokens);
		freeTokens(tokens);
		cmd = commands;
		while (cmd != NULL)
		{
			executeCommand(cmd);
			cmd = cmd->next;
		}
		freeCommands(commands);
		input = readline("shell> ");
	}
	return (0);
}
