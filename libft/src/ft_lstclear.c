/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:29:08 by codespace         #+#    #+#             */
/*   Updated: 2024/08/29 00:30:06 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*current;

	if (lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		temp = current;
		del(current->content);
		current = current->next;
		free(temp);
	}
	*lst = NULL;
}
