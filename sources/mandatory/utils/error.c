/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:49:55 by codespace         #+#    #+#             */
/*   Updated: 2024/09/12 18:20:47 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

int	ft_syntax_error(char *token)
{
	ft_printf("minishell: syntax error near unexpected token `%s'\n", token);
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

int	throw_error(char *cmd_path)
{
	if (*cmd_path == '\0')
		cmd_path = " ";
	if (access(cmd_path, X_OK) == -1 && !access(cmd_path, F_OK))
	{
		printf("%s: Permission denied\n", cmd_path);
		return (126);
	}
	else if ((*cmd_path == '.' || ft_strchr(cmd_path, '/')) && !access(cmd_path,
			F_OK))
	{
		printf("%s: Is a directory\n", cmd_path);
		return (126);
	}
	else if (errno == 2 || !getenv("PATH"))
	{
		printf("%s: No such file or directory\n", cmd_path);
		return (127);
	}
	else
		return (!!write(STDERR_FILENO, "minishell: unexpected error\n", 28));
}
