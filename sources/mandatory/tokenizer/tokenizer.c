/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 23:12:15 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/04/13 23:22:51 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/mini_shell.h"

Token	*tokenizeInput(char *input)
{
	Token	*head;
	Token	**current;

	head = NULL;
	current = &head;
	iterateTokens(input, current);
	return (head);
}

void	iterateTokens(char *input, Token **current)
{
	char	*start;
	char	*cursor;

	start = input;
	cursor = input;
	while (*cursor)
	{
		if (isInsideQuotes(cursor))
			cursor = skipQuotes(cursor);
		else if (isOperatorOrEnd(cursor))
		{
			if (start < cursor)
			{
				*current = createToken(start, TOKEN_WORD);
				current = &(*current)->next;
			}
			if (isOperatorChar(*cursor))
			{
				*current = createToken(cursor, TOKEN_OPERATOR);
				current = &(*current)->next;
			}
			start = cursor + 1;
		}
		cursor++;
	}
}

bool	isInsideQuotes(char *cursor)
{
	return (*cursor == '\'' || *cursor == '\"');
}

char	*skipQuotes(char *cursor)
{
	char	quoteType;

	quoteType = *cursor;
	cursor++;
	while (*cursor && *cursor != quoteType)
		cursor++;
	return (cursor);
}

bool	isOperatorOrEnd(char *cursor)
{
	return (isOperatorChar(*cursor) || *(cursor + 1) == '\0');
}
