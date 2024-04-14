/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 23:12:15 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/04/14 13:19:20 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

bool	is_operator_char(char c)
{
	return (ft_strchr(" \t\n|&;()<>", c) != NULL);
}

bool	is_inside_quotes(char *cursor)
{
	return (*cursor == '\'' || *cursor == '\"');
}

char	*skip_quotes(char *cursor)
{
	char	quotetype;

	quotetype = *cursor;
	cursor++;
	while (*cursor && *cursor != quotetype)
		cursor++;
	return (cursor);
}

bool	is_operator_or_end(char *cursor)
{
	return (is_operator_char(*cursor) || *(cursor + 1) == '\0');
}
