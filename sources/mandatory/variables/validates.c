/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validates.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:34:18 by roglopes          #+#    #+#             */
/*   Updated: 2024/04/13 15:34:35 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
** Validação de nome de variável. O nome da variável pode conter apenas letras
** (a a z ou A a Z), números (0 a 9) ou sublinhado (_). O
** o primeiro caractere não pode ser um número.
** PARÂMETROS
**#1. Os ponteiros para o nome da variável (var_name);
** VALORES DE RETORNO
** Retorna verdadeiro se o nome da variável contém apenas caracteres permitidos é falso ou se não é.
*/
#include "../../includes/mandatory/mini_shell.h"

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
