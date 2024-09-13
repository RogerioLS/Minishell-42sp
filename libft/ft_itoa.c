/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:56:32 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/09/12 21:06:06 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*ascii;
	int		len;
	long	nbr;

	len = ft_nbrlen(n, 10);
	nbr = n;
	if (nbr < 0)
	{
		nbr = -nbr;
		len++;
	}
	ascii = ft_dalloc(sizeof(char), (len + 1));
	if (ascii == NULL)
		return (NULL);
	ascii[len] = '\0';
	while (len > 0)
	{
		ascii[--len] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	if (n < 0)
		ascii[0] = '-';
	return (ascii);
}
