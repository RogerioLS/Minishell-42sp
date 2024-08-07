/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:34:21 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/03/01 04:34:23 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*go_malloc(size_t size, int type)
{
	char	*str;

	str = (char *)ft_calloc(size, type);
	if (str == NULL)
		return (NULL);
	if (size == 1)
		*str = '\0';
	return (str);
}

void	generate_result(char *dst, char *entry, int start, int stop)
{
	int	index;

	index = 0;
	while (start <= stop)
	{
		*(dst + index) = *(entry + start);
		start++;
		index++;
	}
	*(dst + index) = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		stop;

	if (set == NULL || s1 == NULL)
		return ((char *)s1);
	start = 0;
	while (ft_strchr(set, s1[start]) != NULL && s1[start] != '\0')
		start++;
	stop = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[stop]) != NULL && stop > start)
		stop--;
	if (stop < start)
		str = go_malloc(1, sizeof(char));
	else
	{
		str = go_malloc(stop - start + 2, sizeof(char));
		if (str == NULL)
			return (NULL);
		generate_result(str, (char *)s1, start, stop);
	}
	return (str);
}
