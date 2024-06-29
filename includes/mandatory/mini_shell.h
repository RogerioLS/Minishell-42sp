/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:52:11 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/29 16:00:38 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "../../libft/include/ft_printf.h"
# include "../../libft/include/get_next_line.h"
# include "../../libft/include/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <grp.h>
# include <limits.h>
# include <linux/limits.h>
# include <pwd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define MAX_PATH_LEN 1024
# define ARG_MAX 4096 // Máximo do próprio shell//

enum					e_token_type
{
	TOKEN_WORD,
	TOKEN_OPERATOR,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_PIPE,
	TOKEN_DOLLAR,
	TOKEN_L_PAREN,
	TOKEN_R_PAREN,
	TOKEN_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_L_REDIR,
	TOKEN_R_REDIR
};

typedef struct s_mini
{
	char				*name;
	char				*cmd_line;
	int					exported;
	int					aftercmd;
	struct s_mini		*next;
}						t_mini;

typedef struct s_token
{
	char				*text;
	enum e_token_type	type;
	struct s_token		*next;
}						t_token;

typedef struct s_alias
{
	char				*name;
	char				*command;
	struct s_alias		*next;
}						t_alias;

typedef struct s_command
{
	char				*text;
	struct s_command	*next;
}						t_command;

// Main
void					initialize(void);
void					process_command_line(t_mini *mini);
void					main_loop(t_mini *mini);

// Prompt
char					*prompt(void);
void					parse_input(char *input, char *result);
void					handle_double_quotes(char **input, char *result,
							size_t *res_len);
void					handle_single_quotes(char **input, char *result,
							size_t *res_len);
void					append_var_value(char **input, char *result, \
						size_t *res_len);
void					get_var_name(char **input, char *varname, \
						int *len);

// Signal
void					handle_signal(int sign);
int						afterprompt(int is_after);

// Tokenizer
t_token					*input_tokenizer(char *input);
t_token					*create_token(const char *text, enum e_token_type type);
char					**tokens_to_argv(t_token *tokens);
bool					is_operator_char(char c);
bool					is_inside_quotes(char *cursor);
char					*skip_quotes(char *cursor);
bool					is_operator_or_end(char *cursor);
int						classify_token(const char *token);

// Expansion
char					*expand_variable(const char *variable);
void					append_variable_expanded(char **expanded,
							const char **cursor);
void					append_char_expanded(char **expanded,
							const char **cursor);
void					expand_token(t_token *token);
void					expand_variables_tokens(t_token *head);
void					append_value(char **expanded, const char *value);
char					*get_variable_name(const char **cursor);

// Command
void					print_environment(void);
int						handle_redirection(char **tokens, int *input_fd,
							int *output_fd, int i);
int						handle_heredoc(char **tokens, int i);
void					handle_redirection_and_execution(char **tokens,
							int input_fd, int output_fd);

// Command 2
char					*find_command_path(char **paths, char *command);
int						execute_found_command(char *full_path, char **args);
int						execute_external_command(char **args);
void					handle_internal_command(char **args);
void					execute_command(char **args);

// Command 3
char					***parse_commands_with_pipes(char **args);
int						count_pipes(char **args);
char					***allocate_commands(int num_pipes);
void					split_commands(char **args, char ***commands);
void					execute_pipeline(char ***commands);

// Command 4
int						count_commands(char ***commands);
void					create_pipes(int *pipefds, int num_pipes);
void					close_pipes(int *pipefds, int num_pipes);
void					setup_redirection(int *pipefds, int num_pipes, int i);
void					execute_command_in_pipeline(char **command, \
						int *pipefds, int num_pipes, int i);

// Builtins
void					export_variable(char **args);
char					*ft_realpath(const char *path,
							char *resolved_path);
void					ft_pwd(int argc, char **argv);
void					ft_echo(char **args);
void					clear_screen(void);
void					ft_cd(char *path);

// Utils
char					*ft_strtok(char *str, const char *delim);
char					*ft_strspn_end(char *str, const char *delim);
size_t					ft_strcspn(const char *s, const char *reject);
size_t					ft_strspn(const char *s, const char *accept);
int						ft_lstsize_token(t_token *head);
void					ft_unset(char **args);
void					ft_valid_malloc(int *pipefds);

// Free
void					ft_free_commands(t_command *head);
void					ft_free_tokens(t_token *head);
void					ft_free_string_array(char **array);
char					*ft_strjoin_free(char *s1, char *s2);
void					free_commands(char ***commands);

#endif
