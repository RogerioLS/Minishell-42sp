/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:28:58 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/01 19:43:32 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

char	*expand_variable(const char *variable)
{
	char	*value;
	char	*expanded_value;

	value = getenv(variable);
	if (value)
	{
		expanded_value = strdup(value);
		if (!expanded_value)
		{
			perror("strdup failed");
			return (NULL);
		}
		return (expanded_value);
	}
	return (NULL);
}

void	append_variable_expanded(char **expanded, const char **cursor)
{
	size_t	name_length;
	char	*name;
	char	*value;

	(*cursor)++;
	name_length = ft_strcspn(*cursor, " $/\t\n,.'\"");
	// strndup not implemantion
	name = strndup(*cursor, name_length);
	if (!name)
	{
		perror("malloc failed");
		free(*expanded);
		exit(EXIT_FAILURE);
	}
	value = expand_variable(name);
	free(name);
	if (value)
	{
		*expanded = realloc(*expanded, ft_strlen(*expanded) + ft_strlen(value) + 1);
		if (!*expanded)
		{
			perror("realloc failed");
			exit(EXIT_FAILURE);
		}
		// not are implementation
		strcat(*expanded, value);
		free(value);
	}
	*cursor += name_length;
}

void	append_char_expanded(char **expanded, const char **cursor)
{
	size_t	current_length;

	current_length = ft_strlen(*expanded);
	*expanded = realloc(*expanded, current_length + 2);
	if (!*expanded)
	{
		perror("realloc failed");
		exit(EXIT_FAILURE);
	}
	(*expanded)[current_length] = **cursor;
	(*expanded)[current_length + 1] = '\0';
	(*cursor)++;
}

void	expand_token(t_token *token)
{
	const char	*cursor;
	char		*expanded;

	cursor = token->text;
	expanded = malloc(ft_strlen(token->text) + 1);
	if (!expanded)
	{
		perror("malloc failed");
		return ;
	}
	expanded[0] = '\0';
	while (*cursor)
	{
		if (*cursor == '$')
		{
			append_variable_expanded(&expanded, &cursor);
		}
		else
		{
			append_char_expanded(&expanded, &cursor);
		}
	}
	free(token->text);
	token->text = expanded;
}

void	expand_variables_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		expand_token(current);
		current = current->next;
	}
}
