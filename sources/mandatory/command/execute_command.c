/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:48:42 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/02 18:33:57 by roglopes         ###   ########.fr       */
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

void	ft_free_string_array(char **array)
{
	if (!array)
		return ; // Nada a liberar se o array for nulo

	for (int i = 0; array[i]; i++)
	{
		free(array[i]);
	}
	free(array);
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

char ***parse_commands_with_pipes(char **args)
{
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

/* int execute_external_command(char **args)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	path_env = getenv("PATH");
	if (!path_env)
	{
		ft_printf("command not found: %s\n", args[0]);
		return (0);
	}

	paths = ft_split(path_env, ':');
	full_path = NULL;
	i = 0;

	while (paths[i] != NULL)
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin_free(full_path, args[0]);
		if (access(full_path, X_OK) == 0)
		{
			pid_t pid = fork();
			if (pid == 0)
			{
				execve(full_path, args, NULL);
				perror("execve");
				exit(EXIT_FAILURE);
			}
			else if (pid > 0)
			{
				int status;
				waitpid(pid, &status, 0);
				if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {}
				free(full_path);
				ft_free_string_array(paths);
				return (1);
			}
			else
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
		}
		free(full_path);
		i++;
	}
	ft_free_string_array(paths);
	return (0);
} */

// Função para buscar o caminho completo do comando
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

// Função para executar o comando encontrado
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
	return (0);  // Nunca alcançado, mas evita aviso de compilador
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

// old execute_command --------------------------------
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

void	execute_command(char **args)
{
	char ***commands;

	if (args[0] == NULL)
		return ;

	commands = parse_commands_with_pipes(args);

	if (commands[1] != NULL)
		execute_pipeline(commands);
	else
	{
		handle_internal_command(args);
		if (ft_strcmp(args[0], "pwd") != 0 && ft_strcmp(args[0], "clear") != 0 \
		&& ft_strcmp(args[0], "exit") != 0 && ft_strcmp(args[0], "cd") != 0 \
		&& ft_strcmp(args[0], "export") != 0 && ft_strcmp(args[0], "unset") != 0 \
		&& ft_strcmp(args[0], "env") != 0 && ft_strcmp(args[0], "echo") != 0)
		{
			if (!execute_external_command(args))
				ft_printf("command not found: %s\n", args[0]);
		}
	}
}

// old handle_redirection_and_execution -------
int	handle_redirection(char **tokens, int *input_fd,\
						int *output_fd, int i)
{
	if (tokens[i + 1] == NULL)
	{
		printf("syntax error near unexpected token 'newline'\n");
		return (-1);
	}
	if (strcmp(tokens[i], ">") == 0)
		*output_fd = open(tokens[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (strcmp(tokens[i], ">>") == 0)
		*output_fd = open(tokens[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (strcmp(tokens[i], "<") == 0)
		*input_fd = open(tokens[i + 1], O_RDONLY);
	if (*output_fd < 0 || *input_fd < 0)
	{
		perror("open failed");
		return (-1);
	}
	tokens[i] = NULL;
	tokens[i + 1] = NULL;
	return (0);
}

int	handle_heredoc(char **tokens, int i)
{
	char	*delimiter;
	char	*line;
	size_t	bufsize;
	ssize_t	chars_read;

	delimiter = tokens[i + 1];
	if (delimiter == NULL)
	{
		printf("syntax error near unexpected token 'newline'\n");
		return (-1);
	}
	tokens[i] = NULL;
	tokens[i + 1] = NULL;
	line = NULL;
	bufsize = 0;
	while ((chars_read = getline(&line, &bufsize, stdin)) != -1)
	{
		if (strcmp(line, delimiter) == 0)
			break ;
	}
	free(line);
	return (0);
}

void	handle_redirection_and_execution(char **tokens, \
										int input_fd, int output_fd)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (strcmp(tokens[i], ">") == 0 || \
		strcmp(tokens[i], ">>") == 0 || strcmp(tokens[i], "<") == 0)
		{
			if (handle_redirection(tokens, &input_fd, &output_fd, i) == -1)
				return ;
		}
		else if (strcmp(tokens[i], "<<") == 0)
		{
			if (handle_heredoc(tokens, i) == -1)
				return ;
		}
		i++;
	}
	execute_command(tokens);
}


//*Init de uma global pra sinais
// volatile sig_atomic_t stop = 0;

// void handle_sig(int signum) {
//     if (isatty(STDIN_FILENO)) {
//         if (signum == SIGINT) {
//             rl_on_new_line();
//             rl_replace_line("", 0);
//             ft_putstr_fd("\n", STDOUT_FILENO);
//             if (!afterprompt(-1)) {
//                 rl_redisplay();
//             }
//             stop = 1;
//         } else if (signum == SIGQUIT) {
//             // Tratamento para SIGQUIT, se necessário
//         } else if (signum == SIGTERM) {
//             write(STDOUT_FILENO, "exit\n", 5);
//             exit(EXIT_SUCCESS);
//         }
//     } else 
//     {
//     }
// }

//*ESSE Heredoc funciona com o retorno do delimiter
// void handle_redirection_and_execution(char **tokens, int input_fd, int output_fd) {
//     int i = 0;
//     char *delimiter = NULL;

//     signal(SIGINT, handle_sig); // Configurar manipulador de sinal para Ctrl+C

//     while (tokens[i] != NULL) {
//         if (strcmp(tokens[i], "<") == 0) {
//             if (tokens[i + 1] == NULL) {
//                 printf("syntax error near unexpected token 'newline'\n");
//                 return;
//             }
//             input_fd = open(tokens[i + 1], O_RDONLY);
//             if (input_fd < 0) {
//                 perror("open failed");
//                 return;
//             }
//             tokens[i] = NULL;
//             tokens[i + 1] = NULL;
//         } else if (strcmp(tokens[i], ">") == 0) {
//             if (tokens[i + 1] == NULL) {
//                 printf("syntax error near unexpected token 'newline'\n");
//                 return;
//             }
//             output_fd = open(tokens[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
//             if (output_fd < 0) {
//                 perror("open failed");
//                 return;
//             }
//             tokens[i] = NULL;
//             tokens[i + 1] = NULL;
//         } else if (strcmp(tokens[i], ">>") == 0) {
//             if (tokens[i + 1] == NULL) {
//                 printf("syntax error near unexpected token 'newline'\n");
//                 return;
//             }
//             output_fd = open(tokens[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
//             if (output_fd < 0) {
//                 perror("open failed");
//                 return;
//             }
//             tokens[i] = NULL;
//             tokens[i + 1] = NULL;
//         } else if (strcmp(tokens[i], "<<") == 0) {
//             if (tokens[i + 1] == NULL) {
//                 printf("syntax error near unexpected token 'newline'\n");
//                 return;
//             }
//             delimiter = strdup(tokens[i + 1]);
//             tokens[i] = NULL;
//             tokens[i + 1] = NULL;

//             // Ler o heredoc diretamente do arquivo
//             FILE *heredoc_file = fopen("/dev/stdin", "r");
//             if (!heredoc_file) {
//                 perror("fopen");
//                 return;
//             }

//             char *line = NULL;
//             size_t bufsize = 0;
//             ssize_t chars_read;

//             // Buffer para armazenar todas as linhas do heredoc
//             char *heredoc_buffer = malloc(1);
//             heredoc_buffer[0] = '\0';
//             size_t heredoc_size = 1;

//             // Loop para ler as linhas do heredoc até encontrar o delimitador ou Ctrl+C
//             while (!stop && (chars_read = getline(&line, &bufsize, heredoc_file)) != -1) {
//                 // Remover o '\n' do final da linha para comparação com o delimitador
//                 line[strcspn(line, "\n")] = '\0';

//                 if (strcmp(line, delimiter) == 0) {
//                     break;
//                 }

//                 // Adicionar a linha lida ao buffer do heredoc
//                 heredoc_size += strlen(line) + 1;
//                 heredoc_buffer = realloc(heredoc_buffer, heredoc_size);
//                 strcat(heredoc_buffer, line);
//                 strcat(heredoc_buffer, "\n");
//             }

//             if (stop) {
//                 // Se Ctrl+C foi pressionado, liberar recursos e retornar ao prompt
//                 free(line);
//                 free(delimiter);
//                 free(heredoc_buffer);
//                 stop = 0;
//                 fclose(heredoc_file);
//                 return;
//             }
//             ft_printf("%s", heredoc_buffer);
//             free(line);
//             free(delimiter);
//             free(heredoc_buffer);
//             fclose(heredoc_file);
//             return;
//         }
//         i++;
//     }
//     execute_command(tokens);
//     if (input_fd != STDIN_FILENO) {
//         close(input_fd);
//     }
//     if (output_fd != STDOUT_FILENO) {
//         close(output_fd);
//     }
// }
