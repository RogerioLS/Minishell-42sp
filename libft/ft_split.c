/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:52:25 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/13 16:28:05 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char *str, char delimiter)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != delimiter)
		{
			count++;
			while (str[i] != delimiter && str[i])
			{
				i++;
			}
		}
		if (str[i])
			i++;
	}
	return (count);
}

static int	ft_wordlen(char *str, char c)
{
	int	count;

	count = 0;
	while (str[count] != c && str[count])
		count++;
	return (count);
}

static void	ft_addword(char *src, char *dst, char c)
{
	int	i;

	i = 0;
	while (i < ft_wordlen(src, c))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

static void	*ft_rollback(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		words;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	words = ft_countwords((char *)s, c);
	arr = (char **)ft_dalloc((words + 1), sizeof(char *));
	if (arr == NULL)
		return (NULL);
	while (i < words)
	{
		while (*s == c)
			s++;
		arr[i] = (char *)ft_dalloc((ft_wordlen((char *)s, c) + 1), 1);
		if (arr[i] == NULL)
			return (ft_rollback(arr));
		ft_addword((char *)s, arr[i], c);
		i++;
		while (*s != c && *s)
			s++;
	}
	arr[i] = NULL;
	return (arr);
}
