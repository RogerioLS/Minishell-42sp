/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:25:15 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/01/05 17:52:32 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*ocurrence;
	size_t	lil_len;
	size_t	c;

	ocurrence = NULL;
	lil_len = ft_strlen(little);
	c = 0;
	while (big[c] && c < len && lil_len)
	{
		if (!ft_strncmp((big + c), little, lil_len) && (c + lil_len <= len))
		{
			ocurrence = (char *)(big + c);
			break ;
		}
		c++;
	}
	if (!lil_len)
		ocurrence = (char *)big;
	return (ocurrence);
}
