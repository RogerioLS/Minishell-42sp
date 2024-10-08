/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:01:23 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/13 16:28:05 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		s1_len;
	const char	*s1_last;
	char		*str;

	if (!s1 || !set)
		return (NULL);
	s1_len = ft_strlen(s1);
	s1_last = &s1[s1_len - 1];
	while (ft_strchr(set, *s1) && *s1)
	{
		s1++;
	}
	while (ft_strchr(set, *s1_last) && *s1_last)
	{
		s1_last--;
	}
	str = ft_substr(s1, 0, ft_strlen(s1) - ft_strlen(s1_last) + 1);
	return (str);
}
