/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:11:32 by codespace         #+#    #+#             */
/*   Updated: 2024/08/29 18:43:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

char	*ft_substr(char const *input, unsigned int start, size_t length)
{
	char	*substr;
	size_t	s_len;

	s_len = ft_strlen((char *)input);
	if (start > s_len)
		return (ft_calloc(1, 1));
	if (s_len - start >= length)
		substr = ft_dalloc((length + 1), sizeof(char));
	else
		substr = ft_dalloc((s_len - start + 1), sizeof(char));
	if (substr != NULL)
	{
		ft_strlcpy(substr, (&input[start]), (length + 1));
		return (substr);
	}
	return (NULL);
}
