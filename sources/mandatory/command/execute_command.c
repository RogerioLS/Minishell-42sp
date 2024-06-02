/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:48:42 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/02 18:23:43 by roglopes         ###   ########.fr       */
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

char ***parse_commands_with_pipes(char **args) {
    int num_pipes = 0;
    int i = 0;

    // Contar o número de pipes
    while (args[i] != NULL) {
        if (strcmp(args[i], "|") == 0) {
            num_pipes++;
        }
        i++;
    }

    char ***commands = malloc((num_pipes + 2) * sizeof(char **));
    if (!commands) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    int cmd_idx = 0;
    commands[cmd_idx] = args;
    i = 0;
    while (args[i] != NULL) {
        if (strcmp(args[i], "|") == 0) {
            args[i] = NULL;
            commands[++cmd_idx] = &args[i + 1];
        }
        i++;
    }
    commands[cmd_idx + 1] = NULL;

    return commands;
}

void execute_pipeline(char ***commands)
{
    int num_commands = 0;
    while (commands[num_commands] != NULL) {
        num_commands++;
    }

    int pipefds[2 * (num_commands - 1)];
    int i = 0;

    while (i < num_commands - 1) {
        if (pipe(pipefds + i*2) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    i = 0;
    while (i < num_commands) {
        pid_t pid = fork();
        if (pid == 0) {
            if (i > 0) {
                if (dup2(pipefds[(i-1)*2], 0) == -1) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            if (i < num_commands - 1) {
                if (dup2(pipefds[i*2 + 1], 1) == -1) {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            int j = 0;
            while (j < 2 * (num_commands - 1)) {
                close(pipefds[j]);
                j++;
            }

            execvp(commands[i][0], commands[i]);
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    i = 0;
    while (i < 2 * (num_commands - 1)) {
        close(pipefds[i]);
        i++;
    }

    i = 0;
    while (i < num_commands) {
        wait(NULL);
        i++;
    }
}

void ft_free_string_array(char **array) {
    if (!array) {
        return;
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
    char *full_path;
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
                if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {}
                free(full_path);
                ft_free_string_array(paths);
                return 1;
            } else {
                perror("fork");
                exit(EXIT_FAILURE);
            }
        }
        free(full_path);
        i++;
    }
    ft_free_string_array(paths);
    return 0;
}

void execute_command(char **args) {
    if (args[0] == NULL) {
        return;
    }

    char ***commands = parse_commands_with_pipes(args);
    if (commands[1] != NULL) {
        execute_pipeline(commands);
    } else {
        if (ft_strcmp(args[0], "pwd") == 0) { ft_pwd(0, args); }
        else if (ft_strcmp(args[0], "clear") == 0) { clear_screen(); }
        else if (ft_strcmp(args[0], "exit") == 0) { exit(EXIT_SUCCESS); }
        else if (ft_strcmp(args[0], "cd") == 0) { ft_cd(args[1]); }
        else if (ft_strcmp(args[0], "export") == 0) { export_variable(args); }
        else if (ft_strcmp(args[0], "unset") == 0) { ft_unset(args); }
        else if (ft_strcmp(args[0], "env") == 0) { print_environment(); }
        else if (ft_strcmp(args[0], "echo") == 0) { ft_echo(args); }
        else { 
            if (!execute_external_command(args)) {
                ft_printf("command not found: %s\n", args[0]);
            }
        }
    }
    free(commands);
}

char *read_command(void) {
    char *cmd_line = prompt();
    if (!cmd_line) {
        ft_printf("\n");
        exit(EXIT_SUCCESS);
    }
    char *expanded_cmd_line = expandVariables(cmd_line);
    free(cmd_line);
    return expanded_cmd_line;
}

void handle_redirection_and_execution(char **tokens, int input_fd, int output_fd) {
    int i = 0;
    char *delimiter = NULL;

    while (tokens[i] != NULL) {
        if (ft_strcmp(tokens[i], ">") == 0 || strcmp(tokens[i], ">>") == 0 || ft_strcmp(tokens[i], "<") == 0) {
            if (tokens[i + 1] == NULL) {
                ft_printf("syntax error near unexpected token 'newline'\n");
                return;
            }

            if (ft_strcmp(tokens[i], ">") == 0) {
                output_fd = open(tokens[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
            } else if (ft_strcmp(tokens[i], ">>") == 0) {
                output_fd = open(tokens[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
            } else if (ft_strcmp(tokens[i], "<") == 0) {
                input_fd = open(tokens[i + 1], O_RDONLY);
            }

            if (output_fd < 0 || input_fd < 0) {
                perror("open failed");
                return;
            }

            tokens[i] = NULL;
            tokens[i + 1] = NULL;
        } else if (strcmp(tokens[i], "<<") == 0) {
            if (tokens[i + 1] == NULL) {
                ft_printf("syntax error near unexpected token 'newline'\n");
                return;
            }

            delimiter = tokens[i + 1];
            tokens[i] = NULL;
            tokens[i + 1] = NULL;
            char *line = NULL;
            size_t bufsize = 0;
            ssize_t chars_read;
            while ((chars_read = getline(&line, &bufsize, stdin)) != -1) {
                if (ft_strcmp(line, delimiter) == 0) {
                    break;
                }
            }
            free(line);
        }
        i++;
    }
    execute_command(tokens);
}
