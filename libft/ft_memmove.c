/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:44:12 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/13 16:28:05 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*udest;
	unsigned char	*usrc;

	i = 0;
	udest = (unsigned char *)dest;
	usrc = (unsigned char *)src;
	if (!udest && !usrc)
		return (0);
	if (udest < usrc)
	{
		while (i < n)
		{
			udest[i] = usrc[i];
			i++;
		}
		return (udest);
	}
	i = n - 1;
	while (i < n)
	{
		udest[i] = usrc[i];
		i--;
	}
	return (udest);
}
