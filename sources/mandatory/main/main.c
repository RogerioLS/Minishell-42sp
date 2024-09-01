/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:24:12 by codespace         #+#    #+#             */
/*   Updated: 2024/09/01 19:49:07 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

void	initialize(void)
{
	ft_print_welcome( );
	printf("\033[1;33m\nMINIHELL started!\033[0m\n");
}

char	*ft_init_and_wait_input(t_token **list)
{
	char	*line;

	if (ft_setup_signal_handler(ft_main_signal_handler) != SUCCESS)
	{
		ft_free_env(-1);
		ft_free_memory();
		exit(ft_signal_error());
	}
	*list = NULL;
	line = readline("\033[1;34mMini-Sell> $ ➜ \033[0m");
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

void	ft_print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		printf("Token: %s, Type: %i\n", current->value, current->type);
		current = current->next;
	}
}

int	main(void)
{
	char		*input;
	t_token		*tokens;
	t_tree_node	*tree;

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
				printf("Lexer success\n");
				ft_print_tokens(tokens);
				if (ft_parser(tokens, &tree) == SUCCESS)
				{
					//ft_set_exit_status();
					printf("Parser success\n");
				}
			}
		}
	}
	return (0);
}
