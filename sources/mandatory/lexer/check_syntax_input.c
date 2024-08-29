/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:53:19 by codespace         #+#    #+#             */
/*   Updated: 2024/08/29 13:41:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

int	ft_check_syntax_input(char *input)
{
	int	index;
	int	single_quote;
	int	double_quote;

	index = 0;
	single_quote = 0;
	double_quote = 0;
	while (input[index])
	{
		if (input[index] == '\'' || input[index] == '\"')
			ft_move_to_next_quote(input, &index, &single_quote, &double_quote);
		index++;
	}
	if (single_quote != 0 || double_quote != 0)
	{
		write(STDERR_FILENO, INVALID_QUOTE, 57);
		return (SYNTAX_ERROR);
	}
	return (SUCCESS);
}

void	ft_move_to_next_quote(char *input, int *index, int *single_quote,
		int *double_quote)
{
	if (input[*index] == '\'')
	{
		(*single_quote)++;
		(*index)++;
		while (input[*index] && input[*index] != '\'')
			(*index)++;
		if (input[*index] == '\'')
			(*single_quote)--;
	}
	if (input[*index] == '\"')
	{
		(*double_quote)++;
		(*index)++;
		while (input[*index] && input[*index] != '\"')
			(*index)++;
		if (input[*index] == '\"')
			(*double_quote)--;
	}
}
