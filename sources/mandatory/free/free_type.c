/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 00:34:57 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/04/14 00:35:42 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/mini_shell.h"

void	freeTokens(Token *head)
{
	Token	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->text);
		free(temp);
	}
}

void	freeCommands(Command *head)
{
	Command	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->text);
		free(temp);
	}
}
