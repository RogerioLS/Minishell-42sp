/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:34:09 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/09/12 21:06:56 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		s_size;

	s_size = ft_strlen((char *)s) + 1;
	dup = ft_dalloc(sizeof(char), s_size);
	if (dup == NULL)
		return (NULL);
	dup = ft_memcpy(dup, s, s_size);
	return (dup);
}

char    *ft_strdup_malloc(const char *s)
{
    char    *str;
    int        len;

    len = ft_strlen(s) + 1;
    str = (char *) malloc(len * sizeof(char));
    if (str == NULL)
        return (NULL);
    ft_strlcpy(str, s, len);
    return (str);
}

char    *ft_strdup_calloc(const char *s)
{
    size_t    len;
    size_t    i;
    char    *p;

    len = ft_strlen(s);
    p = (char *)malloc(len + 1 * sizeof(char));
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
