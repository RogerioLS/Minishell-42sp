/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:24:10 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/01/05 17:53:24 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	alloc_mem(char **split_array, char const *s, char c)
{
	int	index;
	int	letters;

	index = 0;
	letters = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			while (*s != c && *s != '\0')
			{
				letters++;
				s++;
			}
			split_array[index] = (char *)ft_calloc(letters + 1, sizeof(char));
			index++;
			letters = 0;
		}
		else
			s++;
	}
}

static int	count_word(const char *s, char c)
{
	int	index;
	int	words;

	index = 0;
	words = 0;
	while (s[index] != '\0')
	{
		if (s[index] != c)
		{
			words++;
			while (s[index] != c && s[index] != '\0')
				index++;
		}
		else
			index++;
	}
	return (words);
}

static void	fill_array(char **result_array, const char *s, char c)
{
	int	word;
	int	letters;

	word = 0;
	letters = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			while (*s != c && *s != '\0')
			{
				result_array[word][letters] = *s;
				s++;
				letters++;
			}
			word++;
			letters = 0;
		}
		else
			s++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		words;

	words = count_word(s, c);
	result = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!s || !result)
		return (NULL);
	alloc_mem(result, s, c);
	fill_array(result, s, c);
	return (result);
}
