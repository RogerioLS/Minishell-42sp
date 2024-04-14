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

void	handle_signal(int sign)
{
	if (sign == SIGINT)
	{
		printf("\n\033[1;31mMINIHELL>$\033[0m ");
		fflush(stdout);
	}
	else if (sign == SIGQUIT)
	{
	}
	else if (sign == SIGTERM)
	{
	}
	else if (sign == SIGTSTP)
	{
	}
	else if (sign == SIGTTIN)
	{
	}
	else if (sign == SIGTTOU)
	{
	}
	else if (sign == SIGCHLD)
	{
	}
	else if (sign == SIGPIPE)
	{
	}
	else if (sign == SIGINT)
	{
	}
	else if (sign == SIGTERM)
	{
		exit(EXIT_SUCCESS); // Ctrl+D || Vai sair do minishell
	}
}
