/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 12:46:39 by roglopes          #+#    #+#             */
/*   Updated: 2024/07/14 12:46:48 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para simular o comando echo
void	my_echo(char *input)
{
	if (input[0] == '$')
	{
		char *env_var = getenv(input + 1); // Ignorar o símbolo $
		if (env_var)
		{
			printf("%s\n", env_var);
		}
		else
		{
			printf("%s: Undefined variable.\n", input + 1);
		}
	}
	else
	{
		printf("%s\n", input);
	}
}

// Função para simular o comando export
void	my_export(char *var, char *value)
{
	if (setenv(var, value, 1) != 0)
	{
		perror("setenv");
	}
}

// Função para simular o comando unset
void	my_unset(char *var)
{
	if (unsetenv(var) != 0)
	{
		perror("unsetenv");
	}
}

int	main(void)
{
	// Teste do comando echo com variáveis de ambiente
	my_echo("$PATH");
	my_echo("$USER");

	// Teste do comando export
	my_export("MY_VAR", "test_value");
	my_echo("$MY_VAR");

	// Teste do comando unset
	my_unset("MY_VAR");
	my_echo("$MY_VAR");

	return (0);
}
