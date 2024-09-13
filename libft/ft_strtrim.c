/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:02:18 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/09/12 21:06:06 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	end;
	size_t	start;
	size_t	len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	while (ft_strchr(set, s1[start]) && s1[start])
		start++;
	end = ft_strlen((char *)s1);
	while (ft_strchr(set, s1[end - 1]) && end)
		end--;
	len = end - start;
	return (ft_substr(s1, start, len));
}
