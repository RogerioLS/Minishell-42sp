/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:58:49 by roglopes          #+#    #+#             */
/*   Updated: 2024/04/07 19:34:03 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../../includes/mandatory/mini_shell.h"
//A primeira etapa de processamento é a leitura do comando.
//Funcao para lidar com entrada do usuario

// para executar o nao esquece de add a flag de readline pois precisamos capturar 
// entrada do usuaruio.
// gcc -o minishell main.c -lreadline
// apos a execucao digite algo.
// para finalizar o programa basta da crtl+d

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/history.h>
#include <readline/readline.h>

typedef enum {
    TOKEN_WORD,
    TOKEN_OPERATOR,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_APPEND_OUT
} TokenType;

typedef struct Token {
    char *text;
    TokenType type;
    struct Token *next;
} Token;

typedef struct Alias {
    char *name;
    char *command;
    struct Alias *next;
} Alias;

typedef enum {
    COMMAND_SIMPLE,
    COMMAND_PIPELINE,
    COMMAND_REDIRECTION_INPUT,
    COMMAND_REDIRECTION_OUTPUT,
    COMMAND_REDIRECTION_APPEND
} CommandType;

typedef struct Command {
    char *text;
    CommandType type;
    struct Command *next;
} Command;

void executeCommand(Command *cmd) {
    char *argv[128];
    int argc = 0;

    char *token = strtok(cmd->text, " ");
    while (token != NULL && argc < 127) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }
    argv[argc] = NULL;

    pid_t pid = fork();
    if (pid == 0) {
        if (execvp(argv[0], argv) == -1) {
            perror("shell");
            exit(EXIT_FAILURE);
        }
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    } else {
        perror("fork");
    }
}

Command *createCommand(char *text, CommandType type) {
    Command *cmd = malloc(sizeof(Command));
    if (!cmd) return NULL;

    cmd->text = strdup(text);
    cmd->type = type;
    cmd->next = NULL;

    return cmd;
}

void appendCommand(Command **head, Command *newCmd) {
    if (!*head) {
        *head = newCmd;
    } else {
        Command *temp = *head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newCmd;
    }
}

Command *parseCommands(Token *tokens) {
    Command *head = NULL;
    Command *currentCommand = NULL;
    char commandText[1024] = "";

    while (tokens != NULL) {
        switch (tokens->type) {
            case TOKEN_WORD:
                if (strlen(commandText) > 0) strcat(commandText, " ");
                strcat(commandText, tokens->text);
                break;
            case TOKEN_PIPE:
                if (strlen(commandText) > 0) {
                    currentCommand = createCommand(commandText, COMMAND_SIMPLE);
                    appendCommand(&head, currentCommand);
                    commandText[0] = '\0';
                }
                if (currentCommand != NULL) currentCommand->type = COMMAND_PIPELINE;
                break;
            default:
                break;
        }
        tokens = tokens->next;
    }
    if (strlen(commandText) > 0) {
        currentCommand = createCommand(commandText, COMMAND_SIMPLE);
        appendCommand(&head, currentCommand);
    }

    return head;
}

void freeCommands(Command *head) {
    while (head != NULL) {
        Command *temp = head;
        head = head->next;
        free(temp->text);
        free(temp);
    }
}

char *expandVariables(const char *input) {
    char *buffer = malloc(strlen(input) + 1);
    if (!buffer) return NULL;
    buffer[0] = '\0';

    const char *cursor = input;
    char *tempCursor;

    while (*cursor) {
        if (*cursor == '$') {
            cursor++;
            size_t varNameLen = strcspn(cursor, " $/\t\n");
            char varName[varNameLen + 1];
            strncpy(varName, cursor, varNameLen);
            varName[varNameLen] = '\0';
            char *varValue = getenv(varName);
            if (varValue) {
                buffer = realloc(buffer, strlen(buffer) + strlen(varValue) + 1);
                strcat(buffer, varValue);
            }
            cursor += varNameLen;
        } else {
            size_t currentLength = strlen(buffer);
            buffer = realloc(buffer, currentLength + 2);
            tempCursor = buffer + currentLength;
            *tempCursor++ = *cursor++;
            *tempCursor = '\0';
        }
    }
    return (buffer);
}

Token *createToken(const char *text, TokenType type) {
    Token *token = malloc(sizeof(Token));
    if (!token) return NULL;
    token->text = strdup(text);
    token->type = type;
    token->next = NULL;
    return token;
}

void freeTokens(Token *head) {
    while (head != NULL) {
        Token *temp = head;
        head = head->next;
        free(temp->text);
        free(temp);
    }
}

bool isOperatorChar(char c) {
    return (strchr(" \t\n|&;()<>", c) != NULL);
}

Token *tokenizeInput(char *input) {
    Token *head = NULL;
    Token **current = &head;
    char *start = input;
    char *cursor = input;
    bool inQuotes = false;
    char quoteType = 0;

    while (*cursor) {
        if (inQuotes) {
            if (*cursor == quoteType) inQuotes = false;
            cursor++;
        } else {
            if (*cursor == '\'' || *cursor == '\"') {
                inQuotes = true;
                quoteType = *cursor;
            } else if (isOperatorChar(*cursor) || *(cursor + 1) == '\0') {
                if (start < cursor) {
                    *current = createToken(start, TOKEN_WORD);
                    current = &(*current)->next;
                }
                if (isOperatorChar(*cursor)) {
                    char op[2] = {*cursor, '\0'};
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
void expandAliases(Token *tokens, Alias *aliasMap) {
    Token *current = tokens;
    while (current != NULL) {
        if (current->type == TOKEN_WORD) {
            Alias *alias = aliasMap;
            while (alias != NULL) {
                if (strcmp(current->text, alias->name) == 0) {
                    free(current->text);
                    current->text = strdup(alias->command);
                    break;
                }
                alias = alias->next;
            }
        }
        current = current->next;
    }
}

int main(void) {
    char *input;
    Alias *aliasMap;

    aliasMap = NULL;
    input = readline("shell> ");
    while (input != NULL) {
        if (strlen(input) > 0) add_history(input);

        char *expandedInput = expandVariables(input);
        free(input);

        Token *tokens = tokenizeInput(expandedInput);
        free(expandedInput);

        expandAliases(tokens, aliasMap);

        Command *commands = parseCommands(tokens);
        freeTokens(tokens);

        Command *cmd = commands;
        while (cmd != NULL) {
            executeCommand(cmd);
            cmd = cmd->next;
        }

        freeCommands(commands);

        input = readline("shell> ");
    }
    return (0);
}
