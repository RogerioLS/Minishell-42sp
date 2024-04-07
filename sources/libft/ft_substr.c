/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:25:27 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/01/05 17:54:33 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*aux_sub;
	size_t	aux_len;

	aux_len = ft_strlen(s);
	if (start > aux_len)
		return (ft_strdup(""));
	if (aux_len >= len)
		aux_len = len;
	if (ft_strlen(s) - start < aux_len)
		aux_len = ft_strlen(&s[start]);
	aux_sub = (char *)ft_calloc(aux_len + 1, sizeof(char));
	if (aux_sub)
		ft_strlcpy(aux_sub, &s[start], aux_len + 1);
	return (aux_sub);
}
