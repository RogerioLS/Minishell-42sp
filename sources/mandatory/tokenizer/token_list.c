/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:52:34 by codespace         #+#    #+#             */
/*   Updated: 2024/08/29 14:05:11 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

t_token	*ft_token_lst_new(char *value, int token_type)
{
	t_token	*new;

	new = ft_dalloc(sizeof(t_token), 1);
	if (!new)
		return (NULL);
	new->type = token_type;
	new->value = value;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	ft_token_lst_add_back(t_token **token_list, t_token *new)
{
	t_token	*last;

	if (!(*token_list))
		*token_list = new;
	else
	{
		last = ft_token_lst_get_last(*token_list);
		last->next = new;
		new->prev = last;
	}
}

int	ft_token_lst_get_size(t_token *token_list)
{
	t_token	*current;
	int		count;

	count = 0;
	current = token_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

t_token	*ft_token_lst_get_last(t_token *token_list)
{
	t_token	*current;

	if (!token_list)
		return (NULL);
	current = token_list;
	while (current->next)
		current = current->next;
	return (current);
}

void	ft_sort_token_lst(t_token **head)
{
	t_token	*current;
	t_token	*next;
	char	*temp;

	current = *head;
	while (current)
	{
		next = current->next;
		while (next)
		{
			if (ft_strcmp(current->value, next->value) > 0)
			{
				temp = current->value;
				current->value = next->value;
				next->value = temp;
			}
			next = next->next;
		}
		current = current->next;
	}
}
