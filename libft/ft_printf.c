/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 01:34:53 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/13 16:28:05 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	int			i;
	int			count;
	t_format	*flags;

	i = 0;
	count = 0;
	flags = (t_format *)malloc(sizeof(t_format));
	if (format == NULL)
		return (-1);
	flags = inicialize_flags(flags);
	va_start(flags->ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i = ft_eval_format(flags, format, i + 1);
			count += ft_print_format(format[i++], flags);
		}
		else
			count += write(1, &format[i++], 1);
		flags = inicialize_flags(flags);
	}
	va_end(flags->ap);
	free(flags);
	return (count);
}
