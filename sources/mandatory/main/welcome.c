/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 18:53:56 by codespace         #+#    #+#             */
/*   Updated: 2024/09/04 19:27:49 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

void	initialize(void)
{
	ft_print_welcome();
	printf("\033[1;33m\nMINIHELL started!\033[0m\n");
}

void	ft_print_welcome(void)
{
	int		fd;
	char	buff[1];
	int		color_code;

	color_code = 31;
	fd = open("assets/welcome.txt", O_RDONLY);
	if (fd == -1)
		return ;
	while (read(fd, buff, 1) > 0)
	{
		printf("\033[0;%dm%c", color_code, buff[0]);
		if (buff[0] == '\n')
			color_code = 31;
		else
		{
			color_code++;
			if (color_code > 36)
				color_code = 31;
		}
	}
	printf("\033[0m");
	close(fd);
}
