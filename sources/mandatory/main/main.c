/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:27:05 by roglopes          #+#    #+#             */
/*   Updated: 2024/05/11 14:09:33 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

void	print_tokens(t_token *head)
{
	while (head != NULL)
	{
		ft_printf("Recebido: %s \nToken de tipo: %d\n\n", head->text, head->type);
		head = head->next;
	}
}

int	main(void)
{
	t_mini	mini;
	t_token	*tokens;
	char	**tokens_parce;

	ft_printf("\033[1;33mMINIHELL started!\033[0m\n");
	// lembrar de pegar prioridade do terminal com term_ios.h
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, handle_signal);
	while (1)
	{
		mini.cmd_line = prompt();
		if (!mini.cmd_line)
		{
			ft_printf("\n");
			exit(EXIT_SUCCESS);
		}
		if (mini.cmd_line && *mini.cmd_line)
		{
			tokens = input_tokenizer(mini.cmd_line);
			tokens_parce = tokens_to_argv(tokens);
			execute_command(tokens_parce, ft_arraylen(tokens_parce));
			// aqui tem que ter as expansões
			//ft_printf("Tamanho da lista %d \n", ft_lstsize_token(tokens));
			//print_tokens(tokens);
			free(tokens_parce);
			ft_free_tokens(tokens);
		}
		free(mini.cmd_line);
	}
	return (0);
}
