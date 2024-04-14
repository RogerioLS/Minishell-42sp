/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lucas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:43:16 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/04/13 18:46:58 by lluiz-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int		last_exit_status = 0;

int	afterprompt(int is_after); // SIGNAL //

char	*prompt(void)
{
	char	*input;

	input = NULL;
	afterprompt(0);
	input = readline("Minihell>$ ");
	if (!input)
	{
		write(STDERR_FILENO, "Error reading input.\n",
			ft_strlen("Error reading input.\n"));
		exit(EXIT_FAILURE);
	}
	afterprompt(1);
	if (input[0] != '\0')
	{
		add_history(input);
	}
	return (input);
}

int	afterprompt(int is_after)
{
	static int	after;

	if (is_after != -1)
		after = is_after;
	return (after);
}

void	handle_signals(int signum)
{
	if (signum == SIGINT)
	{
		// CTRL+C
		write(STDOUT_FILENO, "\nMinihell> ", 11);
	}
	else if (signum == SIGQUIT)
	{
		// CTRL+\ (SIGQUIT)
		_exit(last_exit_status);
	}
}

void	execute_command(char *args[])
{
	pid_t	pid;
		int status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		_exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execvp(args[0], args);
		perror("execvp");
		_exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		last_exit_status = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
	}
}

void	shell_loop(void)
{
	char	input[1024];
	ssize_t	read_bytes;
	int		input_index;
			char *args[50];
	int		argc;

	signal(SIGINT, handle_signals);  // CTRL+C //
	signal(SIGQUIT, handle_signals); // CTRL+\ (SIGQUIT) //
	signal(SIGTSTP, SIG_IGN);        // CTRL+Z (ignorado) //
	input_index = 0;
	while (1)
	{
		write(STDOUT_FILENO, "Minihell> ", 11);
		read_bytes = read(STDIN_FILENO, &input[input_index], 1);
		if (read_bytes < 0)
		{
			perror("read");
			_exit(EXIT_FAILURE);
		}
		if (input[input_index] == '\n')
		{
			input[input_index] = '\0';
			argc = 0;
			args[argc++] = ft_strtok(input, " ");
			while ((args[argc++] = ft_strtok(NULL, " ")) != NULL)
				;
			execute_command(args);
			input_index = 0;
			ft_memset(input, 0, sizeof(input));
		}
		else
		{
			input_index++;
		}
	}
}

int	main(void)
{
	shell_loop();
	return (0);
}

int	tokenization(char *input, char **tokens)
{
	char	*token;
	int		i;

	token = NULL;
	i = 0;
	token = ft_strtok(input, " \n");
	while (token != NULL)
	{
		tokens[i++] = classify_token(token);
		token = ft_strtok(NULL, " \n");
	}
	tokens[i] = NULL;
	return (i);
}

// [UTILS Mandatório para tokenização] //
char	*classify_token(const char *token)
{
	if (!ft_strncmp(token, "<<", 2))
		return ("HEREDOC");
	if (!ft_strncmp(token, ">>", 2))
		return ("APPEND");
	if (*token == '|')
		return ("PIPE");
	if (*token == '$')
		return ("DOLLAR");
	if (*token == '(')
		return ("L_PAREN");
	if (*token == ')')
		return ("R_PAREN");
	if (*token == '\'')
		return ("QUOTE");
	if (*token == '"')
		return ("DOUBLE_QUOTE");
	if (*token == '<')
		return ("L_REDIR");
	if (*token == '>')
		return ("R_REDIR");
	return ("ARGUMENT");
}

void	handle_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN); // Também serve para o CTRL+D //
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
}

//.H minishell //

// enum s_tokens
// {
//     ARGUMENT = 1,
//     APPEND,
//     BLOCK,
//     DOUBLE_QUOTE,
//     DOLLAR,
//     EXEC,
//     HEREDOC,
//     L_PAREN,
//     L_REDIR,
//     PIPE,
//     QUOTE,
//     R_PAREN,
//     R_REDIR,
//     TOKEN_NULL
// };
