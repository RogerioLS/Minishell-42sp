/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_move_next_word.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:36:27 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/13 16:28:05 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*move_quote(char *str, char quote, int *end_word)
{
	if (*str == quote)
	{
		str++;
		if (*str == quote)
			str++;
		else
		{
			*end_word = 1;
			while (*str != quote && *str != '\0')
			{
				str++;
			}
			if (*str != '\0')
				str++;
		}
	}
	return (str);
}

static char	*ft_move_delimiter(char *str, char delimiter)
{
	while (*str == delimiter)
		str++;
	return (str);
}

char	*ft_move_next_word(char *str, char delimiter)
{
	int	end_word;

	end_word = 0;
	str = ft_move_delimiter(str, delimiter);
	while (!end_word)
	{
		if (*str == S_QUOTE)
			str = move_quote(str, S_QUOTE, &end_word);
		else if (*str == D_QUOTE)
			str = move_quote(str, D_QUOTE, &end_word);
		else
		{
			while (*str != S_QUOTE && *str != D_QUOTE && *str != delimiter
				&& *str != '\0')
				str++;
			end_word = 1;
		}
		if (!(*str == delimiter || *str == '\0'))
			end_word = 0;
	}
	str = ft_move_delimiter(str, delimiter);
	return (str);
}
