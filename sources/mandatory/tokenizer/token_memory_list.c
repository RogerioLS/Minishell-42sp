/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_memory_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:58:24 by codespace         #+#    #+#             */
/*   Updated: 2024/08/29 13:59:19 by codespace        ###   ########.fr       */
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
