/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:33:15 by roglopes          #+#    #+#             */
/*   Updated: 2024/04/14 13:12:33 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Verifica se a linha de comando é uma declaração de variável.
** [PARÂMETROS]
**#1. Os ponteiros para linha de comando (cmd);
** [VALORES DE RETORNO]
** Retorna verdadeiro se a linha de comando for uma declaração de variável e falso se não for.
*/
#include "../../../includes/mandatory/mini_shell.h"

bool	commandline_var(char *cmd)
{
	if (ft_strchr(cmd, '=') == NULL)
		return (false);
	return (true);
}
