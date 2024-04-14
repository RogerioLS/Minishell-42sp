/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:27:05 by roglopes          #+#    #+#             */
/*   Updated: 2024/04/14 18:45:37 by roglopes         ###   ########.fr       */
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

int	ft_lstsize(t_token *head)
{
	int	count;

	count = 1;
	if (head == NULL)
		return (0);
	while (head->next != NULL)
	{
		head = head->next;
		count++;
	}
	return (count);
}

// funcao para enfeitar o a palavra MINIHELL started!
// sai em degrader.
void	print_gradient(void)
{
	char	*text;
	int		text_length;
	int		i;
	int		ansi_green;
	int		ansi_red;
	int		length;
	int		step;
	int		ansi_code;

	int green, red;
	length = 30;
	text = "MINIHELL started!";
	text_length = ft_strlen(text);
	step = length / text_length;
	i = 0;
	ft_printf("\033[1;");
	while (i <= length)
	{
		green = (255 * i) / length;
		red = 255 - green;
		ansi_green = (green * 5) / 255;
		ansi_red = (red * 5) / 255;
		ansi_code = 16 + ansi_green * 6 + ansi_red;
		ft_printf("\033[38;5;%dm", ansi_code);
		if (i / step < text_length)
		{
			ft_printf("%c", text[i / step]);
		}
		i++;
	}
	ft_printf("\033[0m\n");
}

int	main(void)
{
	t_mini	mini;
	t_token	*tokens;

	// print_gradient();
	ft_printf("\033[1;33mMINIHELL started!\033[0m\n");
	// lembrar de pegar prioridade do terminal com term_ios.h
	signal(SIGINT, handle_signal);
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
			print_tokens(tokens);
			ft_printf("Tamanho da lista %d \n", ft_lstsize(tokens));
			ft_free_tokens(tokens);
		}
		free(mini.cmd_line);
	}
	return (0);
}
