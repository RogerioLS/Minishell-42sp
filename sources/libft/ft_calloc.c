/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:18:56 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/01/05 17:52:46 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	result;

	ptr = NULL;
	result = nmemb * size;
	if (!nmemb || !size || nmemb == result / size)
		ptr = malloc(result);
	if (ptr)
		ft_bzero(ptr, result);
	return (ptr);
}
