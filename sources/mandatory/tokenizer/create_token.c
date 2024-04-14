/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 23:33:24 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/04/13 23:34:02 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/mini_shell.h"

Token	*createToken(const char *text, TokenType type)
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

// void	freeTokens(Token *head)
// {
// 	Token	*temp;

// 	while (head != NULL)
// 	{
// 		temp = head;
// 		head = head->next;
// 		free(temp->text);
// 		free(temp);
// 	}
// }

bool	isOperatorChar(char c)
{
	return (ft_strchr(" \t\n|&;()<>", c) != NULL);
}
