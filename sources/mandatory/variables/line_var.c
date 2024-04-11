/*
** Verifica se a linha de comando é uma declaração de variável.
** [PARÂMETROS]
**#1. Os ponteiros para linha de comando (cmd);
** [VALORES DE RETORNO]
** Retorna verdadeiro se a linha de comando for uma declaração de variável e falso se não for.
*/
#include "../../../include/mandatory/mini_shell.h"

bool	commandline_var(char *cmd)
{
	if (ft_strchr(cmd, '=') == NULL)
		return (false);
	return (true);
}
