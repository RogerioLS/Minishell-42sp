/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:05:13 by roglopes          #+#    #+#             */
/*   Updated: 2024/04/14 18:07:15 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

int	afterprompt(int is_after)
{
	static int	after;

	if (is_after != -1)
		after = is_after;
	return (after);
}

char	*prompt(void)
{
	char	*cmd_line;

	cmd_line = NULL;
	afterprompt(0);
	cmd_line = readline("\033[1;31mMINIHELL>$\033[0m ");
	if (!cmd_line)
	{
		write(STDERR_FILENO, "Error reading input.\n",
			ft_strlen("Error reading input.\n"));
		exit(EXIT_FAILURE);
	}
	afterprompt(1);
	if (cmd_line[0] != '\0')
	{
		add_history(cmd_line);
	}
	if (cmd_line[0] == '\0' || ft_strchr(cmd_line, ' ') != NULL)
	{
		ft_printf("\U0001F9CA");
	}
	else
	{
		printf("\U0001F525");
	}
	return (cmd_line);
}
