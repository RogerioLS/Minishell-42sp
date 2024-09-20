/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ex_up.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:47:28 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/13 16:28:05 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_ex_up_formated(long n, int base)
{
	int		count;
	char	*symbols;

	count = 0;
	symbols = "0123456789ABCDEF";
	if (n < 0)
		return (ft_print_ex_up_formated(-n, base) + write(1, "-", 1));
	else if (n < base)
		return (write(1, &symbols[n], 1));
	else
	{
		count = ft_print_ex_up_formated(n / base, base);
		return (count + ft_print_ex_up_formated(n % base, base));
	}
}

int	ft_print_ex_up(t_format *flags)
{
	unsigned int	n;
	int				count;

	n = (unsigned int)va_arg(flags->ap, int);
	count = 0;
	if (flags->hash >= 1 && n != 0)
		count += write(1, "0X", 2);
	return (count + ft_print_ex_up_formated(n, 16));
}
