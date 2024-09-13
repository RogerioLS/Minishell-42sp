/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:30:51 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/09/12 21:06:06 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;

	s_len = ft_strlen((char *)s);
	if (start > s_len)
		return (ft_calloc(1, 1));
	if (s_len - start >= len)
		substr = ft_dalloc((len + 1), sizeof(char));
	else
		substr = ft_dalloc((s_len - start + 1), sizeof(char));
	if (substr != NULL)
	{
		ft_strlcpy(substr, (&s[start]), (len + 1));
		return (substr);
	}
	return (NULL);
}
