/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:17:02 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/09/12 21:06:06 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free_str_array(char **str_array)
{
	int	i;

	if (str_array == NULL)
		return (NULL);
	i = 0;
	while (str_array[i] != NULL)
		free(str_array[i++]);
	free(str_array);
	return (NULL);
}
