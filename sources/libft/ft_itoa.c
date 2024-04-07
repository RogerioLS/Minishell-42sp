/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:19:47 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/01/05 17:52:39 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_feedback(int *count, int n)
{
	if (n < 0)
		return (*count += 1, -1);
	return (1);
}

static char	*ft_str_len(unsigned int n, int *count)
{
	char	*str;

	if (n >= 10)
	{
		*count += 1;
		str = ft_str_len(n / 10, count);
	}
	else
		str = (char *)ft_calloc(*count + 1, sizeof(char));
	if (!str)
		return (0);
	return (str);
}

static void	ft_recursive_itoa(unsigned int n, int count, char *str)
{
	if (n >= 10)
		ft_recursive_itoa(n / 10, count - 1, str);
	str[count] = (n % 10) + '0';
}

char	*ft_itoa(int n)
{
	int		count;
	int		signal;
	char	*str;

	count = 1;
	signal = ft_feedback(&count, n);
	str = ft_str_len(n * signal, &count);
	if (!str)
		return (NULL);
	if (signal == -1)
		str[0] = '-';
	ft_recursive_itoa(n * signal, count - 1, str);
	return (str);
}
