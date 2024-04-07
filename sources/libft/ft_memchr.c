/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:21:09 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/01/05 17:53:12 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	letter;
	unsigned char	*string;
	size_t			index;

	letter = (unsigned char)c;
	string = (unsigned char *)s;
	index = 0;
	while (n--)
	{
		if (string[index] == letter)
			return (string + index);
		index++;
	}
	return (NULL);
}
