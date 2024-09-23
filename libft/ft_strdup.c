/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:05:10 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/09/20 16:07:47 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*p;

	len = ft_strlen(s);
	p = (char *)ft_dalloc(len + 1, 1);
	if (p == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strdup_malloc(const char *s)
{
	char	*str;
	int		len;

	len = ft_strlen(s) + 1;
	str = (char *)malloc(len * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s, len);
	return (str);
}
