/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:26:36 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/13 16:28:33 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_base_and_get_length(char *base)
{
	int	base_len;
	int	i;

	base_len = 0;
	while (base[base_len] != '\0')
	{
		if (base[base_len] == '+' || base[base_len] == '-')
			return (0);
		i = base_len + 1;
		while (base[i] != '\0')
		{
			if (base[base_len] == base[i])
				return (0);
			i++;
		}
		base_len++;
	}
	if (base_len < 2)
		return (0);
	return (base_len);
}

int	ft_putnbr_base_fd(long nb, char *base, int fd)
{
	int		counter;
	long	baselen;

	counter = 0;
	baselen = check_base_and_get_length(base);
	if (baselen == 0)
		return (0);
	if (nb < 0)
	{
		counter += write(1, "-", 1);
		nb = nb * -1;
	}
	if (nb >= baselen)
		counter += ft_putnbr_base_fd((nb / baselen), base, fd);
	counter += ft_putchar_fd(base[(nb % baselen)], fd);
	return (counter);
}
