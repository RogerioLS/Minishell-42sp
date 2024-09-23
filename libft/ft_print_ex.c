/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:47:28 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/13 16:28:05 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_ex_formated(long n, int base)
{
	int		count;
	char	*symbols;

	count = 0;
	symbols = "0123456789abcdef";
	if (n < base)
		return (write(1, &symbols[n], 1));
	else
	{
		count = ft_print_ex_formated(n / base, base);
		return (count + ft_print_ex_formated(n % base, base));
	}
}

int	ft_print_ex(t_format *flags)
{
	unsigned long	n;
	int				count;

	count = 0;
	n = (unsigned int)(va_arg(flags->ap, unsigned int));
	if (flags->hash >= 1 && n != 0)
		count += write(1, "0x", 2);
	return (count + ft_print_ex_formated(n, 16));
}
