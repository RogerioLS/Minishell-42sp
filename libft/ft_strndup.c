/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:28:39 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/09/12 21:06:06 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s, int n)
{
	char	*ptr;
	int		i;

	i = 0;
	while (s[i])
		i++;
	if (n < i)
		i = n;
	ptr = ft_dalloc(i + 1, sizeof(ptr));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s && *s && i < n)
		ptr[i++] = *s++;
	ptr[i] = '\0';
	return (ptr);
}
