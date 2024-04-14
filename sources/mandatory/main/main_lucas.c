/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lucas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:43:16 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/04/13 18:46:58 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/mini_shell.h"

//Tudo daqui pra baixo são testes por enquanto

#define TOKEN_WORD 1
#define TOKEN_OPERATOR 2
#define TOKEN_HEREDOC 3
#define TOKEN_APPEND 4
#define TOKEN_PIPE 5
#define TOKEN_DOLLAR 6
#define TOKEN_L_PAREN 7
#define TOKEN_R_PAREN 8
#define TOKEN_QUOTE 9
#define TOKEN_DOUBLE_QUOTE 10
#define TOKEN_L_REDIR 11
#define TOKEN_R_REDIR 12

typedef struct Token {
    char *text;
    int type;
    struct Token *next;
} Token;

Token *create_token(const char *text, int type) {
    Token *token = malloc(sizeof(Token));
    if (!token)
        return NULL;
    token->text = ft_strdup(text);
    token->type = type;
    token->next = NULL;
    return token;
}

Token *input_tokenizer(char *input) {
    Token *head = NULL;
    Token **current = &head;

    char *token;
    token = ft_strtok(input, " ");
    while (token != NULL) {
        int token_type = classify_token(token);
        *current = create_token(token, token_type);
        current = &(*current)->next;
        token = ft_strtok(NULL, " ");
    }

    return head;
}

int afterprompt(int is_after) {
    static int after;
    if (is_after != -1)
        after = is_after;
    return after;
}

int classify_token(const char *token) {
    if (!ft_strncmp(token, "<<", 2))
        return TOKEN_HEREDOC;
    if (!ft_strncmp(token, ">>", 2))
        return TOKEN_APPEND;
    if (*token == '|')
        return TOKEN_PIPE;
    if (*token == '$')
        return TOKEN_DOLLAR;
    if (*token == '(')
        return TOKEN_L_PAREN;
    if (*token == ')')
        return TOKEN_R_PAREN;
    if (*token == '\'')
        return TOKEN_QUOTE;
    if (*token == '"')
        return TOKEN_DOUBLE_QUOTE;
    if (*token == '<')
        return TOKEN_L_REDIR;
    if (*token == '>')
        return TOKEN_R_REDIR;
    return TOKEN_WORD;
}

void print_tokens(Token *head) {
    while (head != NULL) {
        printf("Token: %s, Type: %d\n", head->text, head->type);
        head = head->next;
    }
}

char *prompt(void) {
    char *input;
    afterprompt(0);
    input = readline("Minihell>$ ");
    if (!input) {
        write(STDERR_FILENO, "Error reading input.\n", strlen("Error reading input.\n"));
        exit(EXIT_FAILURE);
    }
    afterprompt(1);
    if (input[0] != '\0') {
        add_history(input);
        ft_antispace(input);
    }
    return input;
}


int main(void) {
    char *cmd_line;
    while (1) {
        cmd_line = prompt();
        if (cmd_line && *cmd_line) {
            Token *tokens = input_tokenizer(cmd_line);
            print_tokens(tokens);
            freeTokens(tokens);
        }
        free(cmd_line);
    }
    return 0;
}

// void	handle_signals(void)
// {
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN); // Também serve para o CTRL+D //
// 	signal(SIGTSTP, SIG_IGN);
// 	signal(SIGTTIN, SIG_IGN);
// 	signal(SIGTTOU, SIG_IGN);
// 	signal(SIGCHLD, SIG_IGN);
// }

//.H minishell //

// enum s_tokens
// {
//     ARGUMENT = 1,
//     APPEND,
//     BLOCK,
//     DOUBLE_QUOTE,
//     DOLLAR,
//     EXEC,
//     HEREDOC,
//     L_PAREN,
//     L_REDIR,
//     PIPE,
//     QUOTE,
//     R_PAREN,
//     R_REDIR,
//     TOKEN_NULL
// };
