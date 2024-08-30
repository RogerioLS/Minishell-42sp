/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:15:28 by roglopes          #+#    #+#             */
/*   Updated: 2024/08/30 19:00:50 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

int	ft_setup_signal_handler(void (*func)(int signum))
{
	struct sigaction	sigint_action;
	struct sigaction	sigquit_action;

	ft_bzero(&sigint_action, sizeof(struct sigaction));
	sigint_action.sa_flags = SA_RESTART;
	sigint_action.sa_handler = func;
	ft_bzero(&sigquit_action, sizeof(struct sigaction));
	sigquit_action.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sigint_action, NULL) == -1
		|| sigaction(SIGQUIT, &sigquit_action, NULL) == -1)
		return (ft_handle_error("sigaction"));
	return (SUCCESS);
}

void	ft_main_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDIN_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ft_free_memory();
		ft_set_exit_status(SIGINT + 128);
	}
}

void	heredoc_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDIN_FILENO, "\n", 1);
		close(STDIN_FILENO);
		ft_free_memory();
		set_exit_status(SIGINT + 128);
	}
}
