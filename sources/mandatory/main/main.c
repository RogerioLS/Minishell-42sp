/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:02:15 by codespace         #+#    #+#             */
/*   Updated: 2024/09/23 18:02:35 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

int	ft_run_minishell(void)
{
	char		*input;
	t_token		*tokens;
	t_tree_node	*tree;

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
					ft_set_exit_status(ft_executor(tree));
			}
		}
		ft_reset_mini(input);
	}
	return (ft_finish_program(SUCCESS));
}

int	main(void)
{
	ft_init_environ();
	ft_terminal_properties();
	// initialize();
	ft_run_minishell();
}
