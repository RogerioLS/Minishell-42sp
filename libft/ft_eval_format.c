/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eval_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:26:39 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/13 16:28:05 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_eval_format(t_format *flags, const char *format, int i)
{
	while (!is_normal_flag(format[i]))
	{
		if (format[i] == '.')
			flags->pnt += 1;
		else if (format[i] == '-')
			flags->dash += 1;
		else if (format[i] == '0')
			flags->zero += 1;
		else if (format[i] == '#')
			flags->hash += 1;
		else if (format[i] == ' ')
			flags->sp += 1;
		else if (format[i] == '+')
			flags->sign += 1;
		i++;
	}
	return (i);
}

int	is_normal_flag(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X' || c == '%')
	{
		return (1);
	}
	else
		return (0);
}

int	ft_print_format(char c, t_format *flags)
{
	int	count;

	count = 0;
	if (c == 'c')
		return (ft_print_char(flags));
	else if (c == 's')
		return (ft_print_str(flags));
	else if (c == 'i' || c == 'd')
		return (ft_print_digit(flags));
	else if (c == 'x')
		return (ft_print_ex(flags));
	else if (c == 'X')
		return (ft_print_ex_up(flags));
	else if (c == 'p')
		return (ft_print_pointer(flags));
	else if (c == 'u')
		return (ft_print_unsigned(flags));
	else if (c == '%')
		return (write(1, "%", 1));
	return (count);
}
