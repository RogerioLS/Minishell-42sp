/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:05:13 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/15 16:52:45 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

void	handle_single_quotes(char **input, char *result, size_t *res_len)
{
	(*input)++;
	while (**input && **input != '\'')
		result[(*res_len)++] = *(*input)++;
	if (**input == '\'')
		(*input)++;
	result[*res_len] = '\0';
}

void	parse_input(char *input, char *result)
{
	size_t	res_len;

	res_len = 0;
	while (*input)
	{
		if (*input == '\"')
			handle_single_quotes(&input, result, &res_len);
		else if (*input == '"')
			handle_double_quotes(&input, result, &res_len);
		else
			result[res_len++] = *input++;
	}
	result[res_len] = '\0';
}

char	*prompt(void)
{
	char	*cmd_line;
	char	*cmd_parser;

	cmd_line = NULL;
	cmd_parser = NULL;
	afterprompt(0);
	cmd_line = readline("\033[1;31mMINIHELL>$\033[0m ");
	if (!cmd_line)
	{
		ft_printf("Error reading input.\n");
		exit(EXIT_FAILURE);
	}
	afterprompt(1);
	if (cmd_line[0] != '\0')
		add_history(cmd_line);
	cmd_parser = (char *)malloc(1024 * sizeof(char));
	if (cmd_parser == NULL)
	{
		ft_printf("Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	parse_input(cmd_line, cmd_parser);
	free(cmd_line);
	return (cmd_parser);
}
