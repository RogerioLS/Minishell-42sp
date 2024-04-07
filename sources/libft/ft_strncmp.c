/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:25:05 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/01/05 17:51:56 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	if (n != 0)
	{
		while (s1[index] && (s1[index] == s2[index]) && index < n - 1)
			index++;
		return ((unsigned char)s1[index] - (unsigned char)s2[index]);
	}
	return (0);
}
