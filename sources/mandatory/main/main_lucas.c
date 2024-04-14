// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main_lucas.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/04/13 18:43:16 by lluiz-de          #+#    #+#             */
// /*   Updated: 2024/04/14 04:20:09 by lluiz-de         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

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

void handle_signal(int sign) {
    if (sign == SIGINT) {
        printf("\n\033[1;31mMINIHELL>$\033[0m ");
        fflush(stdout);
    } else if (sign == SIGQUIT) {
    } else if (sign == SIGTERM) {
    } else if (sign == SIGTSTP) {
    } else if (sign == SIGTTIN) {
    } else if (sign == SIGTTOU) {
    } else if (sign == SIGCHLD) {
    } else if (sign == SIGPIPE) {
    } else if (sign == SIGINT)  {
    } else if (sign == SIGTERM) {
        exit(EXIT_SUCCESS); // Ctrl+D || Vai sair do minishell
    }
}


char *prompt(void) {
    char *input;
    afterprompt(0);
    input = readline("\033[1;31mMINIHELL>$\033[0m ");
    if (!input) {
        write(STDERR_FILENO, "Error reading input.\n", ft_strlen("Error reading input.\n"));
        exit(EXIT_FAILURE);
    }
    afterprompt(1);
    if (input[0] != '\0') {
        add_history(input);
        ft_antispace(input);
    }
    if (input[0] == '\0' || ft_strchr(input, ' ') != NULL) {
        printf("\U0001F9CA ");
    } else {
        printf("\U0001F525 ");
    }
    return input;
}

// void print_tokens(Token *head) {
//     while (head != NULL) {
//         printf("Recebido: %s \nToken de tipo: %d\n\n", head->text, head->type);
//         head = head->next;
//     }
// }

int main(void) {
    printf("\033[1;33mMINIHELL started!\033[0m\n");
    signal(SIGINT, handle_signal);
    
    char *cmd_line;
    while (1) {
        cmd_line = prompt();
        if (!cmd_line) {
            printf("\n");
            exit(EXIT_SUCCESS);
        }
        if (cmd_line && *cmd_line) {
            Token *tokens = input_tokenizer(cmd_line);
            // print_tokens(tokens);
            freetokens(tokens);
        }
        free(cmd_line);
    }
    return 0;
}
