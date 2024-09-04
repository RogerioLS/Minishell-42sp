/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:02:15 by codespace         #+#    #+#             */
/*   Updated: 2024/09/23 17:57:57 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

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

void	ft_terminal_properties(int attribute)
{
	static struct termios	term;

	if (!attribute)
		tcgetattr(STDIN_FILENO, &term);
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	ft_reset_mini(char *line)
{
	ft_terminal_properties(0);
	free(line);
	delete_heredoc_files();
	ft_free_memory();
}

int	ft_finish_program(int status)
{
	ft_free_env();
	ft_free_memory();
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		write(STDOUT_FILENO, "bye bye\n", 5);
	rl_clear_history();
	return (status);
}

int	main(void)
{
	char		*input;
	t_token		*tokens;
	t_tree_node	*tree;

	ft_init_environ();
	ft_terminal_properties(0);
	initialize();
	while (42)
	{
		input = ft_init_and_wait_input(&tokens);
		if (!input)
			break ;
		else if (*input != '\0')
		{
			add_history(input);
			if (ft_lexer(input, &tokens) == SUCCESS)
			{
				if (ft_parser(tokens, &tree) == SUCCESS)
					ft_set_exit_status(executor(tree));
			}
		}
		ft_reset_mini(input);
	}
	return (ft_finish_program(SUCCESS));
}
