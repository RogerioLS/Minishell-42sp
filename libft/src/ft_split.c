/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:33:58 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/03/01 04:33:59 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	count_keywords(char *s, char c)
{
	int	sun_keywords;

	sun_keywords = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			sun_keywords++;
			while (*s && *s != c)
				s++;
		}
	}
	return (sun_keywords);
}

char	**ft_split(char const *s, char c)
{
	char	**s_final;
	int		tlenwords;
	int		len;
	int		index;

	index = -1;
	if (s == NULL)
		return (NULL);
	tlenwords = count_keywords((char *)s, c);
	s_final = (char **)ft_calloc(tlenwords + 1, sizeof(char *));
	if (s_final == NULL)
		return (NULL);
	while (index++, index < tlenwords)
	{
		len = 0;
		while (*s && *s == c)
			s++;
		while (*(s + len) && *(s + len) != c)
			len++;
		*(s_final + index) = ft_substr(s, 0, len);
		if (*(s_final + index) == NULL)
			return (NULL);
		s += len;
	}
	return (s_final);
}
