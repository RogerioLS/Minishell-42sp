/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 06:34:32 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/06/02 12:57:43 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

/* char	*ft_strtok(char *str, const char *delim)
{
	static char	*last;
	char		*ret;

	last = NULL;
	if (str != NULL)
	{
		last = str;
	}
	else if (last == NULL || *last == '\0')
	{
		return (NULL);
	}
	last += ft_strspn(last, delim);
	if (*last == '\0')
	{
		return (NULL);
	}
	ret = last;
	last += ft_strcspn(last, delim);
	if (*last != '\0')
	{
		*last = '\0';
		last++;
	}
	printf("Tokenizing: '%s'\n", ret);
	return (ret);
} */

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last;
	char		*ret;

	if (str != NULL)
	{
		last = str;
	}
	else if (last == NULL || *last == '\0')
	{
		return (NULL);
	}
	last += ft_strspn(last, delim);
	if (*last == '\0')
	{
		return (NULL);
	}
	ret = last;
	last += ft_strcspn(last, delim);
	if (*last != '\0')
	{
		*last = '\0';
		last++;
	}
	else
	{
		last = NULL;
	}
	return (ret);
}

/* we will probably delete */
char	*ft_antispace(char *buff)
{
	int	x;

	x = 0;
	while (buff[x] && (buff[x] == ' ' || buff[x] == '\t'))
		x++;
	return (&buff[x]);
}

/* we will probably delete */
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
