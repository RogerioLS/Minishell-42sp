/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:29:34 by roglopes          #+#    #+#             */
/*   Updated: 2024/07/14 16:31:57 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

void	export_variable(t_token *tokens)
{
	char	*name;
	char	*value;
	t_token	*current;
	char	*equal_sign;

	name = NULL;
	value = NULL;
	current = tokens->next;
	if (current != NULL)
	{
		equal_sign = ft_strchr(current->content, '=');
		if (equal_sign != NULL)
		{
			*equal_sign = '\0';
			name = current->content;
			value = equal_sign +1;
			if (setenv(name, value, 1) != 0)
				perror("setenv");
			*equal_sign = '=';
		}
		else
		{
			if (setenv(current->content, "", 1) != 0)
				perror("setenv");
		}
	}
	else
		print_environment();
}

void	builtins(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (current == NULL || current->content == NULL)
		return ;
	if (ft_strcmp(current->content, "pwd") == 0 || ft_strcmp(current->content,
			"clear") == 0 || ft_strcmp(current->content, "exit") == 0
		|| ft_strcmp(current->content, "cd") == 0 || ft_strcmp(current->content,
			"export") == 0 || ft_strcmp(current->content, "unset") == 0
		|| ft_strcmp(current->content, "env") == 0
		|| ft_strcmp(current->content, "echo") == 0)
	{
		handle_internal_command(current);
	}
}
