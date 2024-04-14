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

// Token	*tokenize_input(char *input)
// {
// 	Token	*head;
// 	Token	**current;

// 	head = NULL;
// 	current = &head;
// 	iterate_tokens(input, current);
// 	return (head);
// }

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
