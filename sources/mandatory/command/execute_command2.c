/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:14:40 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/29 16:58:33 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

int		last_exit_status = 0;

char	*find_command_path(char **paths, t_token *command_token)
{
	int		i;
	char	*full_path;

	if (access(command_token->text, X_OK) == 0)
	{
		return (strdup(command_token->text));
	}
	i = 0;
	while (paths[i] != NULL)
	{
		full_path = malloc(strlen(paths[i]) + strlen(command_token->text) + 2);
		if (!full_path)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		strcpy(full_path, paths[i]);
		strcat(full_path, "/");
		strcat(full_path, command_token->text);
		if (access(full_path, X_OK) == 0)
		{
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

int	execute_found_command(char *full_path, t_token *tokens)
{
	pid_t	pid;
	int		status;
	t_token	*current;
	char	**args;
	int		i;

	current = tokens;
	i = 0;
	// Contar tokens
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	// Alocar array de argumentos
	args = malloc((i + 1) * sizeof(char *));
	if (!args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	// Preencher array de argumentos
	current = tokens;
	i = 0;
	while (current != NULL)
	{
		args[i++] = current->text;
		current = current->next;
	}
	args[i] = NULL;
	pid = fork();
	if (pid == 0)
	{
		execve(full_path, args, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		last_exit_status = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
		free(args);
		return (WIFEXITED(status) && WEXITSTATUS(status) == 0);
	}
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	execute_external_command(t_token *tokens)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		result;

	path_env = getenv("PATH");
	if (!path_env)
	{
		ft_printf("command not found: %s\n", tokens->text);
		return (0);
	}
	paths = ft_split(path_env, ':');
	full_path = find_command_path(paths, tokens);
	if (full_path)
	{
		result = execute_found_command(full_path, tokens);
		free(full_path);
	}
	else
	{
		ft_printf("command not found: %s\n", tokens->text);
		result = 0;
	}
	ft_free_string_array(paths);
	return (result);
}

void	handle_internal_command(t_token *tokens)
{
	if (ft_strcmp(tokens->text, "pwd") == 0)
		ft_pwd(0, tokens);
	else if (ft_strcmp(tokens->text, "clear") == 0)
		clear_screen();
	else if (ft_strcmp(tokens->text, "exit") == 0)
	{
		ft_free_tokens(tokens);
		exit(EXIT_SUCCESS);
	}
	else if (ft_strcmp(tokens->text, "cd") == 0)
		ft_cd(tokens);
	else if (ft_strcmp(tokens->text, "export") == 0)
		export_variable(tokens);
	else if (ft_strcmp(tokens->text, "unset") == 0)
		ft_unset(tokens);
	else if (ft_strcmp(tokens->text, "env") == 0)
		print_environment();
	else if (ft_strcmp(tokens->text, "echo") == 0)
		ft_echo(tokens);
}

void	execute_command(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (current == NULL || current->text == NULL)
		return ;
	if (ft_strcmp(current->text, "pwd") == 0 || ft_strcmp(current->text,
			"clear") == 0 || ft_strcmp(current->text, "exit") == 0
		|| ft_strcmp(current->text, "cd") == 0 || ft_strcmp(current->text,
			"export") == 0 || ft_strcmp(current->text, "unset") == 0
		|| ft_strcmp(current->text, "env") == 0 || ft_strcmp(current->text,
			"echo") == 0)
	{
		handle_internal_command(current);
	}
	else
	{
		if (!execute_external_command(current))
		{
			/* code */
		}
	}
}
