/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_calloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:26:33 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/13 16:28:33 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_calloc(const char *s)
{
	size_t	len;
	size_t	i;
	char	*p;

	len = ft_strlen(s);
	p = (char *)ft_calloc(len + 1, 1);
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
