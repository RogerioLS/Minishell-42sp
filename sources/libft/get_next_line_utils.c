/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:25:48 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/01/05 17:52:21 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_char	*get_letter(char letter)
{
	t_char	*set_char;

	set_char = (t_char *)malloc(sizeof(t_char));
	set_char->single_char = letter;
	set_char->next = NULL;
	return (set_char);
}

void	link_letter(t_char **head, t_char *new_letter)
{
	t_char	*aux;

	if (!new_letter)
		return ;
	if (!*head)
	{
		*head = new_letter;
		return ;
	}
	aux = *head;
	while (aux->next)
		aux = aux->next;
	aux->next = new_letter;
}

char	*free_str(t_char *string)
{
	t_char	*temp;

	temp = string;
	while (temp)
	{
		temp = temp->next;
		free(string);
		string = temp;
	}
	temp = NULL;
	return (NULL);
}
