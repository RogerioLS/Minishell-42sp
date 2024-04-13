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

/* char	*ft_strtok(char *str, const char *delim)
{
	static char	*token;
	static char	*nextToken;
	char		*start;
	char		charisDelimiter;
	const		*end;
	int			*d;

	token = NULL;
	nextToken = NULL;
	if (str != NULL)
		token = str;
	else
		token = nextToken;
	//printf("Comando recebido: %s\n", token);
	if (token == NULL)
		return (NULL);
	start = token;
	end = token;
	while (*end != '\0')
	{
		isDelimiter = 0;
		d = delim;
		while (*d != '\0')
		{
			if (*end == *d)
			{
				isDelimiter = 1;
				break ;
			}
			d++;
		}
		if (isDelimiter)
			break ;
		end++;
	}
	if (*end != '\0')
	{
		*end = '\0';
		nextToken = end + 1;
	}
	else
	{
		nextToken = NULL;
	}
	token = nextToken;
	return (start);
}*/

char	*ft_antispace(char *buff)
{
	int	x;

	x = 0;
	while (buff[x] && (buff[x] == ' ' || buff[x] == '\t'))
		x++;
	printf("Comando recebido: %s\n", &buff[x]);
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
