/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:05:17 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/08/30 18:05:23 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

bool	is_builtin(t_token *tokens)
{
	if (!ft_strcmp(tokens->value, "cd") || !ft_strcmp(tokens->value, "echo")
		|| !ft_strcmp(tokens->value, "env") || !ft_strcmp(tokens->value, "exit")
		|| !ft_strcmp(tokens->value, "export") || !ft_strcmp(tokens->value,
			"pwd") || !ft_strcmp(tokens->value, "unset"))
		return (true);
	return (false);
}

int	execute_builtin(t_token *tokens)
{
	if (!ft_strcmp(tokens->value, "cd"))
		return (execute_cd(tokens));
	if (!ft_strcmp(tokens->value, "echo"))
		return (execute_echo(tokens));
	if (!ft_strcmp(tokens->value, "env"))
		return (execute_env(tokens));
	if (!ft_strcmp(tokens->value, "exit"))
		return (execute_exit(tokens));
	if (!ft_strcmp(tokens->value, "export"))
		return (execute_export(tokens));
	if (!ft_strcmp(tokens->value, "pwd"))
		return (execute_pwd());
	if (!ft_strcmp(tokens->value, "unset"))
		return (execute_unset(tokens));
	return (handle_error("error executing builtin"));
}
