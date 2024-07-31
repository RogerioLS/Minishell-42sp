/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:15:28 by roglopes          #+#    #+#             */
/*   Updated: 2024/07/30 23:24:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

int	inside_heredoc(int inside_heredoc)
{
	static int	heredoc;

	if (inside_heredoc != -1)
		heredoc = inside_heredoc;
	return (heredoc);
}

void	sig_newline(int signum)
{
	(void)signum;
	g_vsig = signum;
	if (inside_heredoc(-1) == TRUE)
	{
		printf("\n");
		close (STDIN_FILENO);
	}
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_vsig = 0;
	}
}

void	handle_signal(int signum)
{
	(void)signum;
	g_vsig = signum;
}

void	init_signals(void)
{
	signal(SIGINT, sig_newline);
	signal(SIGQUIT, SIG_IGN);
}
