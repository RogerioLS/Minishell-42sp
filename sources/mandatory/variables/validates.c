/* 
** Validação de nome de variável. O nome da variável pode conter apenas letras
** (a a z ou A a Z), números (0 a 9) ou sublinhado (_). O
** o primeiro caractere não pode ser um número.
** PARÂMETROS
**#1. Os ponteiros para o nome da variável (var_name);
** VALORES DE RETORNO
** Retorna verdadeiro se o nome da variável contém apenas caracteres permitidos é falso ou se não é.
*/
#include "../../../include/mini_shell.h"

bool	validate_name(char *var_name)
{
	int	i;

	i = 0;
	if (ft_isdigit(var_name[i]))
		return (false);
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
