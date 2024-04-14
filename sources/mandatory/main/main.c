/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:27:05 by roglopes          #+#    #+#             */
/*   Updated: 2024/04/13 20:37:44 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mandatory/mini_shell.h"

void	user_loop(char *cmd_line)
{
	cmd_line = NULL;
	while (1)
	{
		cmd_line = readline(":heart_eyes: mini_shell> ");
		if (!cmd_line)
			break ;
		if (cmd_line && cmd_line)
		{
			add_history(cmd_line);
			//ft_antispace(cmd_line);
			//printf("Comando recebido: %s\n", cmd_line);
			ft_strtok(cmd_line, " ");
		}
		//printf("Comando recebido: %s\n", cmd_line);
		free(cmd_line);
	}
}

int	main(void)
{
	t_mini	mini;

	user_loop(mini.cmd_line);
	return (0);
}
