/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 06:34:32 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/04/13 19:42:40 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/mini_shell.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last = NULL;
	char		*ret;

	if (str)
		last = str;
	if (!last)
		return (NULL);
	ret = last + ft_strspn(last, delim);
	last = ret + ft_strcspn(ret, delim);
	if (last == ret)
		return (last = NULL);
	if (*last)
		*last++ = '\0';
	return (ret);
}

char	*ft_antispace(char *buff)
{
	int	x;

	x = 0;
	while (buff[x] && (buff[x] == ' ' || buff[x] == '\t'))
		x++;
	return (&buff[x]);
}

char	*ft_firstword(char *buff)
{
	char	*aux;
	int		x;

	x = -1;
	aux = ft_strdup(buff);
	aux = ft_antispace(aux);
	while (aux[++x])
		if (ft_isspace(aux[x]))
			break ;
	aux[x] = '\0';
	return (aux);
}
