/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:11:32 by codespace         #+#    #+#             */
/*   Updated: 2024/09/04 21:30:22 by ecoelho-         ###   ########.fr       */
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

char	*ft_strdup_calloc(const char *s)
{
	size_t	len;
	size_t	i;
	char	*p;

	len = ft_strlen(s);
	p = (char *)malloc(len + 1 * sizeof(char));
	if (p == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strndup(char *s, int n)
{
	char	*ptr;
	int		i;

	i = 0;
	while (s[i])
		i++;
	if (n < i)
		i = n;
	ptr = ft_dalloc(i + 1, sizeof(ptr));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s && *s && i < n)
		ptr[i++] = *s++;
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strchr_quote_aware(const char *s, int c)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
		}
		if (s[i] == '\"')
		{
			i++;
			while (s[i] && s[i] != '\"')
				i++;
		}
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
