/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:15:28 by roglopes          #+#    #+#             */
/*   Updated: 2024/04/14 18:16:01 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"
// #include "../../../includes/mandatory/signals.h"

void handle_signal(int signum) {
    if (isatty(STDIN_FILENO)) { 
        if (signum == SIGINT) {

            // write(STDOUT_FILENO, "\n\033[1;31mMINIHELL>$\033[0m ", 24);
				rl_on_new_line();
				rl_replace_line("", 0);
				ft_putstr_fd("\n", 2);
				if (!afterprompt(-1))
				rl_redisplay();
        } else if (signum == SIGQUIT) {
 
        } else if (signum == SIGTERM) {
            write(STDOUT_FILENO, "exit\n", 5);
            exit(EXIT_SUCCESS);
        }
    } else {
    }
}