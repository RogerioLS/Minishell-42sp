/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:14:40 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/16 14:29:22 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

char	*find_command_path(char **paths, char *command)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i] != NULL)
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin_free(full_path, command);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

int	execute_found_command(char *full_path, char **args)
{
	pid_t	pid;
	int		status;

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
		return (WIFEXITED(status) && WEXITSTATUS(status) == 0);
	}
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	execute_external_command(char **args)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		result;

	path_env = getenv("PATH");
	if (!path_env)
	{
		ft_printf("command not found: %s\n", args[0]);
		return (0);
	}
	paths = ft_split(path_env, ':');
	full_path = find_command_path(paths, args[0]);
	if (full_path)
	{
		result = execute_found_command(full_path, args);
		free(full_path);
	}
	else
	{
		ft_printf("command not found: %s\n", args[0]);
		result = 0;
	}
	ft_free_string_array(paths);
	return (result);
}

void	handle_internal_command(char **args)
{
	if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd(0, args);
	else if (ft_strcmp(args[0], "clear") == 0)
		clear_screen();
	else if (ft_strcmp(args[0], "exit") == 0)
		exit(EXIT_SUCCESS);
	else if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(args[1]);
	else if (ft_strcmp(args[0], "export") == 0)
		export_variable(args);
	else if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(args);
	else if (ft_strcmp(args[0], "env") == 0)
		print_environment();
	else if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(args);
}

void execute_command(char **args)
{
    char ***commands;

    if (args[0] == NULL)
        return;
    commands = parse_commands_with_pipes(args);
    if (commands[1] != NULL)
        execute_pipeline(commands);
    else
    {
        if (ft_strcmp(args[0], "pwd") == 0 || ft_strcmp(args[0], "clear") == 0 ||
            ft_strcmp(args[0], "exit") == 0 || ft_strcmp(args[0], "cd") == 0 ||
            ft_strcmp(args[0], "export") == 0 || ft_strcmp(args[0], "unset") == 0 ||
            ft_strcmp(args[0], "env") == 0 || ft_strcmp(args[0], "echo") == 0)
        {
            handle_internal_command(args);
        }
        else
        {
            if (!execute_external_command(args)) 
            {
            }
        }
    
