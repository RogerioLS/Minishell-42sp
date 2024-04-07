/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:17:09 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/01/05 17:54:09 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		nb;
	int		sign;
	char	*string;

	sign = 1;
	string = (char *)nptr;
	while ((*string >= 9 && *string <= 13) || *string == 32)
		string++;
	while (*string == '-' || *string == '+')
	{
		if (*(string + 1) == '-' || *(string + 1) == '+')
			return (0);
		if (*string == '-')
			sign = -1;
		string++;
	}
	nb = 0;
	while (*string >= '0' && *string <= '9')
	{
		nb *= 10;
		nb += *string - 48;
		string++;
	}
	return (nb *= sign);
}
