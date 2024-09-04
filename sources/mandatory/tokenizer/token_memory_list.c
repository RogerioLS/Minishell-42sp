/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_memory_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:58:24 by codespace         #+#    #+#             */
/*   Updated: 2024/09/04 19:41:48 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

t_list	**ft_get_memory_lst(void)
{
	static t_list	*lst;

	return (&lst);
}

void	ft_collect_mem(void *content)
{
	ft_lstadd_back(ft_get_memory_lst(), ft_lstnew(content));
}

void	*ft_dalloc(size_t nmemb, size_t size)
{
	void	*p;

	p = ft_calloc(nmemb, size);
	ft_collect_mem(p);
	return (p);
}

char	*ft_strjoin_mini(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)ft_dalloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
