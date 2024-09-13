/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:32:34 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/09/12 21:06:06 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	str = ft_dalloc(sizeof(char), (ft_strlen((char *)s) + 1));
	i = 0;
	if (str != NULL)
	{
		while (s[i] != '\0')
		{
			str[i] = f(i, s[i]);
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}
