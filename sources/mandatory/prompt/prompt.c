/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:05:13 by roglopes          #+#    #+#             */
/*   Updated: 2024/07/13 16:59:44 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

void	print_tokens(t_token *head)
{
	while (head != NULL)
	{
		ft_printf("Recebido: %s \n", head->content);
		head = head->next;
	}
}

void	initialize_lists(t_token **token_list, t_tree **tree_list)
{
	ft_printf("\033[1;33mMINIHELL started!\033[0m\n");
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, handle_signal);
	*token_list = malloc(sizeof(t_token *) + 1);
	*tree_list = malloc(sizeof(t_tree *) + 1);
	*token_list = NULL;
	*tree_list = NULL;
}

int	prompt(void)
{
	char		*input;
	t_token		*tokens;
	t_tree		*in_tree;

	initialize_lists(&tokens, &in_tree);
	input = readline("\033[1;31mMINIHELL>$\033[0m ");
	if (!ft_strncmp(input, "", 1))
		return (0);
	add_history(input);
	if (initialize_checker(input))
	{
		if (initialize_buildtoken(input, &tokens) == ERROR)
			return (0);
		//eotokens(&tokens, &in_tree);
		builtins(tokens);
		//initialize_execution(&in_tree, &tokens);
		print_tokens(tokens);
		free(input);
	}
	free_list(&in_tree, &tokens);
	return (1);
}
