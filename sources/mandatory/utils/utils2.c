/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:41:51 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/04/13 19:42:09 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/mini_shell.h"

// retorna o comprimento do segmento inicial de (s) que não contém nenhum caractere que está presente na string reject. Ele vai buscar o primeiro caractere de s que está em reject e retorna o índice onde ele está.
size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if (s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

// retorna o comprimento do segmento inicial de (s) que contém apenas caracteres que estão presentes na string accept. Ele vai buscar o primeiro caractere de s que não está em accept e retorna o índice onde ele está.
size_t ft_strspn(const char *s, const char *accept)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (accept[j])
		{
			if (s[i] == accept[j])
				break ;
			j++;
		}
		if (!accept[j])
			return (i);
		i++;
	}
	return (i);
}


// percorre a string s e, para cada caractere, verifica se ele está presente na string accept. Se encontrar um caractere correspondente, retorna um ponteiro para esse caractere em s. Se nenhum caractere correspondente for encontrado, retorna NULL.
char	*strpbrk(const char *s, const char *accept)
{
	while (*s != '\0')
	{
		const char *p = accept;
		while (*p != '\0')
		{
			if (*s == *p)
			{
				return ((char *)s);
			}
			p++;
		}
		s++;
	}
	return (NULL);
}
