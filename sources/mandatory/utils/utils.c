/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 06:34:32 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/04/07 06:34:37 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/mandatory/mini_shell.h"

char *ft_strtok(char *str, const char *delim) {
    static char *token = NULL;
    static char *nextToken = NULL;
    if (str != NULL)
        token = str;
    else
        token = nextToken;
    if (token == NULL)
        return NULL;
    char *start = token;
    char *end = token;
    while (*end != '\0') {
        int isDelimiter = 0;
        const char *d = delim;
        while (*d != '\0') {
            if (*end == *d) {
                isDelimiter = 1;
                break;
            }
            d++;
        }
        if (isDelimiter)
            break;
        end++;
    }
    if (*end != '\0') {
        *end = '\0';
        nextToken = end + 1;
    } else {
        nextToken = NULL;
    }
    token = nextToken;
    return start;
}

char	*ft_antispace(char *buff)
{
	int x;

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
