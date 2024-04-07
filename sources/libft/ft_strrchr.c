/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:25:19 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/01/05 17:55:14 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				index;
	unsigned char	*string;

	string = (unsigned char *)s;
	index = ft_strlen(s);
	while (index)
	{
		if (string[index] == (unsigned char)c)
			return ((char *)(string + index));
		--index;
	}
	if (string[index] == (unsigned char)c)
		return ((char *)(string + index));
	return (NULL);
}
