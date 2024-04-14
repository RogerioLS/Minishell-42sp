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

// void process_word(char *start, char *end, Token **current);
// void process_operator(char *operator_char, Token **current);

// void iterate_tokens(char *input, Token **current)
// {
//     char *start = input;
//     char *cursor = input;

//     while (*cursor)
//     {
//         if (is_inside_quotes(cursor))
//             cursor = skip_quotes(cursor);
//         else if (is_operator_or_end(cursor))
//         {
//             if (start < cursor)
//                 process_word(start, cursor, current);

//             if (is_operator_char(*cursor))
//                 process_operator(cursor, current);

//             start = cursor + 1;
//         }
//         cursor++;
//     }
// }

// void process_word(char *start, char *end, Token **current)
// {
//     char *classification = classify_token(start);
//     TokenType token_type;

//     if (strcmp(classification, "HEREDOC") == 0)
//         token_type = TOKEN_HEREDOC;
//     else if (strcmp(classification, "APPEND") == 0)
//         token_type = TOKEN_APPEND;
//     else if (strcmp(classification, "PIPE") == 0)
//         token_type = TOKEN_PIPE;
//     else if (strcmp(classification, "DOLLAR") == 0)
//         token_type = TOKEN_DOLLAR;
//     else if (strcmp(classification, "L_PAREN") == 0)
//         token_type = TOKEN_L_PAREN;
//     else if (strcmp(classification, "R_PAREN") == 0)
//         token_type = TOKEN_R_PAREN;
//     else if (strcmp(classification, "QUOTE") == 0)
//         token_type = TOKEN_QUOTE;
//     else if (strcmp(classification, "DOUBLE_QUOTE") == 0)
//         token_type = TOKEN_DOUBLE_QUOTE;
//     else if (strcmp(classification, "L_REDIR") == 0)
//         token_type = TOKEN_L_REDIR;
//     else if (strcmp(classification, "R_REDIR") == 0)
//         token_type = TOKEN_R_REDIR;
//     else
//         token_type = TOKEN_WORD;

//     *current = create_token(start, token_type);
//     current = &(*current)->next;
// }

// void process_operator(char *operator_char, Token **current)
// {
//     *current = create_token(operator_char, TOKEN_OPERATOR);
//     current = &(*current)->next;
// }

// char	*classify_token(const char *token)
// {
// 	if (!ft_strncmp(token, "<<", 2))
// 		return ("HEREDOC");
// 	if (!ft_strncmp(token, ">>", 2))
// 		return ("APPEND");
// 	if (*token == '|')
// 		return ("PIPE");
// 	if (*token == '$')
// 		return ("DOLLAR");
// 	if (*token == '(')
// 		return ("L_PAREN");
// 	if (*token == ')')
// 		return ("R_PAREN");
// 	if (*token == '\'')
// 		return ("QUOTE");
// 	if (*token == '"')
// 		return ("DOUBLE_QUOTE");
// 	if (*token == '<')
// 		return ("L_REDIR");
// 	if (*token == '>')
// 		return ("R_REDIR");
// 	return ("ARGUMENT");
// }
