/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:43:03 by codespace         #+#    #+#             */
/*   Updated: 2024/09/23 20:42:44 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

int	ft_lexer(char *input, t_token **tokens)
{
	int		token_type;
	int		length;
	t_token	*token;

	if (!input || ft_check_syntax_input(input) == FAILURE)
		return (ft_set_exit_status(SYNTAX_ERROR));
	while (*input)
	{
		length = 0;
		token_type = ft_get_token_type(input);
		if (token_type == SPACES)
			input++;
		else
		{
			length = ft_get_token_length(input, token_type);
			token = ft_token_lst_new(ft_substr(input, 0, length), token_type);
			ft_token_lst_add_back(tokens, token);
			input += length;
		}
	}
	return (SUCCESS);
}

int	ft_get_token_type(char *input)
{
	if (ft_strncmp(input, "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(input, ">>", 2) == 0)
		return (REDIR_APPEND);
	else if (ft_strncmp(input, "<<", 2) == 0)
		return (REDIR_HEREDOC);
	else if (ft_strncmp(input, "<", 1) == 0)
		return (REDIR_IN);
	else if (ft_strncmp(input, ">", 1) == 0)
		return (REDIR_OUT);
	else if (ft_isspace(*input))
		return (SPACES);
	else if (ft_strncmp(input, "\0", 1) == 0)
		return (END);
	else
		return (WORD);
}

int	ft_get_token_length(char *input, int token_type)
{
	if (token_type == PIPE || token_type == REDIR_IN || token_type == REDIR_OUT)
		return (1);
	else if (token_type == REDIR_APPEND || token_type == REDIR_HEREDOC)
		return (2);
	else if (token_type == WORD)
		return (ft_get_word_length(input));
	return (0);
}

int	ft_get_word_length(char *input)
{
	int	len;

	len = 0;
	while (ft_get_token_type(input + len) == WORD)
	{
		if (input[len] == '\'')
		{
			len++;
			while (input[len] != '\'')
				len++;
		}
		if (input[len] == '\"')
		{
			len++;
			while (input[len] != '\"')
				len++;
		}
		len++;
	}
	return (len);
}
