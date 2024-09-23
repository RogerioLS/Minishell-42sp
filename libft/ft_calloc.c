/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:51:58 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/13 16:28:05 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*alloc;
	size_t	total_size;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	total_size = (nmemb * size);
	if ((total_size > 2147483647) || (total_size / nmemb != size))
		return (NULL);
	alloc = malloc(total_size);
	if (alloc != NULL)
		ft_bzero(alloc, total_size);
	return (alloc);
}
