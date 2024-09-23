/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:28:02 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/09/23 16:40:30 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*ft_init_and_wait_input(t_token **list)
{
	char	*line;

	if (ft_setup_signal_handler(ft_main_signal_handler) != SUCCESS)
	{
		ft_free_env();
		ft_free_memory();
		exit(ft_signal_error());
	}
	*list = NULL;
	line = readline("\033[1;34mMini-Shell> $ ➜ \033[0m");
	return (line);
}

void	ft_terminal_properties(void)
{
	static struct termios	term;
	static int				attribute;

	attribute = 0;
	if (!attribute)
		tcgetattr(STDIN_FILENO, &term);
	else
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		attribute = 1;
	}
}

void	ft_reset_mini(char *line)
{
	ft_terminal_properties();
	free(line);
	delete_heredoc_files();
	ft_free_memory();
}

int	ft_finish_program(int status)
{
	ft_free_env();
	ft_free_memory();
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		write(STDOUT_FILENO, "\nbye\n", 5);
	rl_clear_history();
	return (status);
}
