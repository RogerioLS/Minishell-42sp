/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 23:33:24 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/06/02 12:51:20 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

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

t_token	*create_token(const char *text, enum e_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	token->text = ft_strdup(text);
	if (!token->text)
	{
		free(token);
		perror("ft_strdup");
		exit(EXIT_FAILURE);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

/* we will probably delete */
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

t_token	*input_tokenizer(char *input)
{
	t_token	*head;
	t_token	**current;
	char	*token;
	//char	quote;

	head = NULL;
	current = &head;
	token = ft_strtok(input, " ");
	while (token)
	{
		/* if (*token == '\'' || *token == '"')
		{
			quote = *token++;
			token = ft_strtok(NULL, &quote);
		} */
		*current = create_token(token, classify_token(token));
		current = &(*current)->next;
		token = ft_strtok(NULL, " ");
	}
	return (head);
}
