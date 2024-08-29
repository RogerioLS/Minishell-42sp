/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:49:55 by codespace         #+#    #+#             */
/*   Updated: 2024/08/29 19:48:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

int	ft_syntax_error(char *token)
{
	ft_printf("minishell: syntax error near unexpected token `%s'\n",
		token);
	return (ft_set_exit_status(SYNTAX_ERROR));
}

int	ft_handle_error(char *message)
{
	if (*message == '\0')
		message = " ";
	ft_printf("%s: %s\n", message, strerror(errno));
	ft_free_memory();
	return (!!errno);
}

int	ft_signal_error(void)
{
	ft_printf("minishell: failed to install signal handler\n");
	return (FAILURE);
}
