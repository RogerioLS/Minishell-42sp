/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:24:05 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/13 16:28:05 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		i;
	long	num;

	num = n;
	if (num == 0)
		return (ft_strdup("0"));
	i = ft_numlen(num);
	s = (char *)ft_dalloc((i + 1), sizeof(char));
	if (s == NULL)
		return (NULL);
	s[i--] = '\0';
	if (num < 0)
	{
		num *= -1;
		s[0] = '-';
	}
	while (num != 0)
	{
		s[i] = (num % 10) + '0';
		num /= 10;
		i--;
	}
	return (s);
}
