//#include "../../../includes/mandatory/mini_shell.h"
include <stdio.h>
include <stdlib.h>
include <readline/history.h>
include <readline/readline.h>
//A primeira etapa de processamento é a leitura do comando.
//Funcao para lidar com entrada do usuario

// para executar o nao esquece de add a flag de readline pois precisamos capturar 
// entrada do usuaruio.
// gcc -o minishell main.c -lreadline
// apos a execucao digite algo.
// para finalizar o programa basta da crtl+d
void	user_loop(void)
{
	char	input;

	while (1)
	{
		input = readline("mini_shell> ");
		if (!input)
			break ;
		if (input &&input)
			add_history(input);
		printf("Comando recebido: %s\n", input);
		free(input);
	}
}

int	main(void)
{
	user_loop();
	return (0);
}