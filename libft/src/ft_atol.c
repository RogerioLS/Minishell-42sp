/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 21:02:17 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/31 21:02:49 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

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