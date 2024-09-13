/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 17:45:37 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/09/12 21:06:06 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	if (s == NULL)
		return (NULL);
	p = (unsigned char *)s;
	while (n-- > 0)
		*p++ = c;
	return (s);
}
