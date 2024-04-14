/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 23:33:24 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/04/14 01:17:33 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/mini_shell.h"

Token	*create_token(const char *text, TokenType type)
{
	Token	*token;

	token = malloc(sizeof(Token));
	if (!token)
		return (NULL);
	token->text = ft_strdup(text);
	token->type = type;
	token->next = NULL;
	return (token);
}

Token	*tokenize_input(char *input)
{
	Token	*head;
	Token	**current;

	head = NULL;
	current = &head;
	iterate_tokens(input, current);
	return (head);
}

void	iterate_tokens(char *input, Token **current)
{
	char	*start;
	char	*cursor;

	start = input;
	cursor = input;
	while (*cursor)
	{
		if (is_inside_quotes(cursor))
			cursor = skip_quotes(cursor);
		else if (is_operator_or_end(cursor))
		{
			if (start < cursor)
			{
				*current = create_token(start, TOKEN_WORD);
				current = &(*current)->next;
			}
			if (is_operator_char(*cursor))
			{
				*current = create_token(cursor, TOKEN_OPERATOR);
				current = &(*current)->next;
			}
			start = cursor + 1;
		}
		cursor++;
	}
}


//Tudo daqui pra baixo são testes por enquanto

// #define TOKEN_WORD 1
// #define TOKEN_OPERATOR 2
// #define TOKEN_HEREDOC 3
// #define TOKEN_APPEND 4
// #define TOKEN_PIPE 5
// #define TOKEN_DOLLAR 6
// #define TOKEN_L_PAREN 7
// #define TOKEN_R_PAREN 8
// #define TOKEN_QUOTE 9
// #define TOKEN_DOUBLE_QUOTE 10
// #define TOKEN_L_REDIR 11
// #define TOKEN_R_REDIR 12

// typedef struct Token {
//     char *text;
//     int type;
//     struct Token *next;
// } Token;

// Token *create_token(const char *text, int type) {
//     Token *token = malloc(sizeof(Token));
//     if (!token)
//         return NULL;
//     token->text = ft_strdup(text);
//     token->type = type;
//     token->next = NULL;
//     return token;
// }

// Token *tokenize_input(char *input) {
//     Token *head = NULL;
//     Token **current = &head;

//     char *token;
//     token = ft_strtok(input, " ");
//     while (token != NULL) {
//         int token_type = classify_token(token);
//         *current = create_token(token, token_type);
//         current = &(*current)->next;
//         token = ft_strtok(NULL, " ");
//     }

//     return head;
// }

// int classify_token(const char *token) {
//     if (!strncmp(token, "<<", 2))
//         return TOKEN_HEREDOC;
//     if (!strncmp(token, ">>", 2))
//         return TOKEN_APPEND;
//     if (*token == '|')
//         return TOKEN_PIPE;
//     if (*token == '$')
//         return TOKEN_DOLLAR;
//     if (*token == '(')
//         return TOKEN_L_PAREN;
//     if (*token == ')')
//         return TOKEN_R_PAREN;
//     if (*token == '\'')
//         return TOKEN_QUOTE;
//     if (*token == '"')
//         return TOKEN_DOUBLE_QUOTE;
//     if (*token == '<')
//         return TOKEN_L_REDIR;
//     if (*token == '>')
//         return TOKEN_R_REDIR;
//     return TOKEN_WORD;
// }

// void print_tokens(Token *head) {
//     while (head != NULL) {
//         printf("Token: %s, Tipo: %d\n", head->text, head->type);
//         head = head->next;
//     }
// }
