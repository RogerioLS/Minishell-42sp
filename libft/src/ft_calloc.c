/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 04:32:28 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/09/04 19:53:53 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*allocate;

	if ((size * nmemb != 0) && (nmemb * size) / size != nmemb)
		return (NULL);
	allocate = malloc(nmemb * size);
	if (allocate != NULL)
		ft_memset(allocate, 0, nmemb * size);
	return (allocate);
}
