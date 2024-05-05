/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 23:33:24 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/05/05 17:50:50 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

// Tudo daqui pra baixo são testes por enquanto
int	classify_token(const char *token)
{
	if (!ft_strncmp(token, "<<", 2))
		return (TOKEN_HEREDOC);
	if (!ft_strncmp(token, ">>", 2))
		return (TOKEN_APPEND);
	if (*token == '|')
		return (TOKEN_PIPE);
	if (*token == '$')
		return (TOKEN_DOLLAR);
	if (*token == '(')
		return (TOKEN_L_PAREN);
	if (*token == ')')
		return (TOKEN_R_PAREN);
	if (*token == '\'')
		return (TOKEN_QUOTE);
	if (*token == '"')
		return (TOKEN_DOUBLE_QUOTE);
	if (*token == '<')
		return (TOKEN_L_REDIR);
	if (*token == '>')
		return (TOKEN_R_REDIR);
	return (TOKEN_WORD);
}

t_token	*create_token(const char *text, TokenType type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->text = ft_strdup(text);
	token->type = type;
	token->next = NULL;
	return (token);
}

void	iterate_tokens(char *input, t_token **current)
{
	char	*start;
	char	*cursor;

	start = input;
	cursor = input;
	while (*cursor)
	{
		if (is_inside_quotes(cursor))
			cursor = skip_quotes(cursor);
		else if (is_operator_or_end(cursor))
		{
			if (start < cursor)
			{
				*current = create_token(start, TOKEN_WORD);
				current = &(*current)->next;
			}
			if (is_operator_char(*cursor))
			{
				*current = create_token(cursor, TOKEN_OPERATOR);
				current = &(*current)->next;
			}
			start = cursor + 1;
		}
		cursor++;
	}
}

char	**tokens_to_argv(t_token *tokens)
{
	int		count;
	char	**args;
	int		i;

	count = ft_lstsize_token(tokens);
	args = malloc((count + 1) * sizeof(char *));
	if (!args)
	{
		perror("malloc() error");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (tokens)
	{
		args[i] = ft_strdup(tokens->text);
		tokens = tokens->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

/* t_token	*tokenize_input(char *input)
{
	t_token	*head;
	t_token	**current;

	head = NULL;
	current = &head;
	iterate_tokens(input, current);
	return (head);
}*/

t_token	*input_tokenizer(char *input)
{
	t_token	*head;
	t_token	**current;
	char	*token;
	int		token_type;

	head = NULL;
	current = &head;
	token = ft_strtok(input, " ");
	while (token != NULL)
	{
		token_type = classify_token(token);
		*current = create_token(token, token_type);
		current = &(*current)->next;
		token = ft_strtok(NULL, " ");
	}
	return (head);
}
