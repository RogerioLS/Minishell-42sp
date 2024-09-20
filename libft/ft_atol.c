/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:13:59 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/13 16:28:05 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(char *str)
{
	char	*c;
	int		i;
	int		sign;
	long	sum;

	i = 0;
	sign = 1;
	c = str;
	sum = 0;
	while ((c[i] >= '\t' && c[i] <= '\r') || c[i] == ' ')
		i++;
	if (c[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (c[i] == '+')
		i++;
	while (ft_isdigit(c[i]))
	{
		sum = (sum * 10) + (c[i] - '0');
		i++;
	}
	return (sum * sign);
}
