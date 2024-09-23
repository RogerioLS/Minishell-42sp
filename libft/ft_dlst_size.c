/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:17:05 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/13 16:28:33 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dlst_size(t_dlst	*list)
{
	int		count;
	t_dlst	*current;

	count = 0;
	current = list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}
