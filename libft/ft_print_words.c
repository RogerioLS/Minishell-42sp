/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:16:40 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/13 16:28:05 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_words(char **str)
{
	int	i;

	i = 0;
	ft_printf("{");
	while (str[i])
	{
		ft_printf("\"%s\", ", str[i]);
		i++;
	}
	if (str[i] == NULL)
		ft_printf("\"NULL\"");
	ft_printf("}\n");
}
