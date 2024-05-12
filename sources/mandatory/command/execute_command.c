/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:48:42 by roglopes          #+#    #+#             */
/*   Updated: 2024/05/11 12:13:59 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

size_t	ft_arraylen(char **array)
{
	size_t	len;

	len = 0;
	while (array[len] != NULL)
	{
		len++;
	}
	return (len);
}

// Forbidden structure
void	print_environment(void)
{
	extern char	**environ;

	for (char **env = environ; *env != NULL; env++)
	{
		ft_printf("%s\n", *env);
	}
}

char *ft_strjoin_free(char *s1, char *s2) {
    if (!s1 || !s2) {
        return NULL;
    }

    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    if (!result) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    strcpy(result, s1);
    strcat(result, s2);

    free(s1);

    return result;
}

void ft_free_string_array(char **array) {
    if (!array) {
        return; // Nada a liberar se o array for nulo
    }

    for (int i = 0; array[i]; i++) {
        free(array[i]);
    }
    free(array);
}


int execute_external_command(char **args) {
    char *path_env = getenv("PATH");
    if (!path_env) {
        ft_printf("command not found: %s\n", args[0]);
        return 0;
    }

    char **paths = ft_split(path_env, ':');
    char *full_path = NULL;
    int i = 0;

    while (paths[i] != NULL) {
        full_path = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin_free(full_path, args[0]);

        if (access(full_path, X_OK) == 0) {
            pid_t pid = fork();

            if (pid == 0) {
                execve(full_path, args, NULL);
                perror("execve");
                exit(EXIT_FAILURE);
            } else if (pid > 0) {
                int status;
                waitpid(pid, &status, 0);
                if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                }
            } else {
                perror("fork");
                exit(EXIT_FAILURE);
            }

            free(full_path);
            ft_free_string_array(paths);
            return 1;
        }

        free(full_path);
        i++;
    }

    ft_free_string_array(paths);
    return 0; // Command not found
}


//EXECUÇÃO DE COMANDOS, APLICAR NA EXTERNAL DEPOIS
// char *ft_path(char *cmd) {
//     if (cmd[0] == '.' && cmd[1] == '/' && access(cmd, X_OK) == 0) {
//         return ft_strdup(cmd);
//     }

//     char *path_env = getenv("PATH");
//     if (!path_env) {
//         return NULL;
//     }

//     char **paths = ft_split(path_env, ':');
//     char *full_path;
//     int i = 0;

//     while (paths[i] != NULL) {
//         full_path = ft_strjoin(paths[i], "/");
//         full_path = ft_strjoin_free(full_path, cmd);

//         if (access(full_path, X_OK) == 0) {
//             ft_free_string_array(paths);
//             return full_path;
//         }

//         free(full_path);
//         i++;
//     }

//     ft_free_string_array(paths);
//     return NULL;
// }



void execute_command(char **args, int argc, int input_fd, int output_fd) {
    if (input_fd != STDIN_FILENO) {
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }
    if (output_fd != STDOUT_FILENO) {
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);
    }

    // Comandos internos
    if (ft_strcmp(args[0], "pwd") == 0) { ft_pwd(argc - 1, args + 1); }
    else if (ft_strcmp(args[0], "clear") == 0) { clear_screen(); }
    else if (ft_strcmp(args[0], "exit") == 0) { exit(EXIT_SUCCESS); }
    else if (ft_strcmp(args[0], "cd") == 0) { ft_cd(args[1]); }
    else if (ft_strcmp(args[0], "export") == 0) { export_variable(args); }
    else if (ft_strcmp(args[0], "unset") == 0) { ft_unset(args); }
    else if (ft_strcmp(args[0], "env") == 0) { print_environment(); }
    else if (ft_strcmp(args[0], "echo") == 0) { ft_echo(args); }
    else { 
        int command_found = execute_external_command(args); 
        if (!command_found) {
            ft_printf("command not found: %s\n", args[0]);
        }
    }
}
