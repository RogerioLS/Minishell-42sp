/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:04:17 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/13 16:28:05 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_quote_split(char *str, char delimiter)
{
	char	**arr;
	int		i;
	int		words;

	i = -1;
	words = ft_countwords_quote(str, delimiter);
	arr = (char **)ft_dalloc((words + 1), sizeof(char *));
	while (++i < words)
	{
		arr[i] = (char *)ft_dalloc(ft_get_len(str, delimiter) + 1, 1);
		ft_add_word(str, delimiter, arr[i]);
		str = ft_move_next_word(str, delimiter);
	}
	arr[i] = NULL;
	return (arr);
}
