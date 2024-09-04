/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 20:16:52 by ecoelho-          #+#    #+#             */
/*   Updated: 2024/09/04 19:43:34 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	**get_cmd_and_args(t_token *cmd)
{
	t_token	*current;
	char	**cmd_and_args;
	int		i;

	cmd_and_args = ft_dalloc(sizeof(char *), (ft_token_lst_get_size(cmd) + 1));
	if (!cmd_and_args)
		ft_handle_error("failed to allocate memory");
	i = 0;
	current = cmd;
	while (current)
	{
		cmd_and_args[i++] = current->value;
		current = current->next;
	}
	cmd_and_args[i] = NULL;
	return (cmd_and_args);
}

char	*search_in_path(t_token *token)
{
	char	*token_path;
	char	*path_env;
	char	**paths;
	int		i;

	path_env = getenv("PATH");
	if (!path_env)
		return (token->value);
	paths = ft_split(path_env, ':');
	if (!paths)
		exit(!!write(STDERR_FILENO, "minishell: failed to retrieve PATH dir \n",
				41));
	i = 0;
	while (paths[i])
	{
		token_path = ft_strjoin_mini(paths[i], "/");
		token_path = ft_strjoin_mini(token_path, token->value);
		if (access(token_path, F_OK) == 0 && access(token_path, X_OK) == 0)
			return (token_path);
		i++;
	}
	printf("%s: command not found\n", token->value);
	ft_free_env();
	ft_free_memory();
	exit(127);
}

char	*get_cmd_path(t_token *token)
{
	char	*token_path;

	if (ft_strcmp(token->value, ".") == 0)
		exit(!!write(STDERR_FILENO, ".:filename argument required\n", 30));
	else if (*(token->value) == '\0')
		token_path = token->value;
	else if (ft_strchr(token->value, '/'))
	{
		token_path = token->value;
		token->value = ft_strrchr(token->value, '/') + 1;
	}
	else
		token_path = search_in_path(token);
	return (token_path);
}

void	run_command_in_child_process(t_token *token)
{
	char	**cmd_and_args;
	char	*cmd_path;
	int		exit_status;

	cmd_path = get_cmd_path(token);
	cmd_and_args = get_cmd_and_args(token);
	if (execve(cmd_path, cmd_and_args, __environ) == -1)
	{
		exit_status = throw_error(cmd_path);
		ft_free_env();
		ft_free_memory();
		exit(exit_status);
	}
}

int	execute_command(t_tree_node *token_node)
{
	int	pid;
	int	exit_status;

	exit_status = 0;
	if (token_node->token)
		expand_tokens(token_node);
	if (token_node->token == NULL)
		return (SUCCESS);
	if (is_builtin(token_node->token))
		return (execute_builtin(token_node->token));
	else
	{
		pid = fork();
		if (pid == -1)
			exit(ft_handle_error("fork"));
		ft_setup_fork_signal_handlers(pid);
		if (pid == 0)
			run_command_in_child_process(token_node->token);
		wait_child_status(pid, &exit_status);
		return (exit_status);
	}
}
