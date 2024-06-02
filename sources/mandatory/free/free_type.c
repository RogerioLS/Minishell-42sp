/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 00:34:57 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/06/01 14:52:06 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

void	ft_free_tokens(t_token *head)
{
	t_token	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->text);
		free(temp);
	}
}

void	ft_free_commands(t_command *head)
{
	t_command	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->text);
		free(temp);
	}
}

void flush_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
