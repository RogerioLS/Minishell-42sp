/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_quote_aware.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:25:35 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/09/12 21:06:06 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_quote_aware(const char *s, int c)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
		}
		if (s[i] == '\"')
		{
			i++;
			while (s[i] && s[i] != '\"')
				i++;
		}
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
