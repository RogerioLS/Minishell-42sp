/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:52:11 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/02 18:27:25 by roglopes         ###   ########.fr       */
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

typedef enum
{
	COMMAND_SIMPLE,
	COMMAND_PIPELINE,
	COMMAND_REDIRECTION_INPUT,
	COMMAND_REDIRECTION_OUTPUT,
	COMMAND_REDIRECTION_APPEND
}						CommandType;

typedef struct s_command
{
	char				*text;
	CommandType			type;
	struct s_command	*next;
}						t_command;

// Tokenizer
t_token					*create_token(const char *text, enum e_token_type type);
t_token					*input_tokenizer(char *input);
bool					is_operator_char(char c);
bool					is_inside_quotes(char *cursor);
char					*skip_quotes(char *cursor);
bool					is_operator_or_end(char *cursor);
int						classify_token(const char *token);
char					**tokens_to_argv(t_token *tokens);

// Utils
char					*ft_strtok(char *str, const char *delim);

/* we will probably delete */
char					*ft_antispace(char *buff);
/* we will probably delete */
char					*ft_firstword(char *buff);

// Utils2
size_t					ft_strcspn(const char *s, const char *reject);
size_t					ft_strspn(const char *s, const char *accept);

// Variables
/* we will probably delete  all*/
int						ft_exit(char *buff);
bool					commandline_var(char *cmd);
bool					validate_name(char *var_name);

// Free
void					ft_free_commands(t_command *head);
void					ft_free_tokens(t_token *head);

// Prompt
char					*prompt(void);
int						afterprompt(int is_after);
void					parse_input(char *input, char *result);
void					handle_double_quotes(char **input, char *result,
							size_t *res_len);
void					handle_single_quotes(char **input, char *result,
							size_t *res_len);

// Signal
void					handle_signal(int sign);

// Command
void					handle_redirection_and_execution(char **tokens,
							int input_fd, int output_fd);
int						handle_heredoc(char **tokens, int i);
int						handle_redirection(char **tokens, int *input_fd,
							int *output_fd, int i);

void					execute_command(char **args);
void					handle_internal_command(char **args);

void					ft_pwd(int argc, char **argv);
void					ft_echo(char **args);
void					ft_unset(char **args);
char					*ft_realpath(const char *path,
							char *resolved_path);

char					*read_command(void);
size_t					ft_arraylen(char **array);
void					export_variable(char **args);
void					ft_cd(char *path);
void					clear_screen(void);
void					print_environment(void);
void					process_arguments(char **args, char *path,
							int *long_format);
void					ft_free_string_array(char **array);
char					*ft_strjoin_free(char *s1, char *s2);
char					***parse_commands_with_pipes(char **args);
void					execute_pipeline(char ***commands);
int						execute_external_command(char **args);

// Command Utils
char					*ft_strcpy(char *dest, const char *src);
void					process_arguments(char **args, char *path,
							int *long_format);
void					print_file_info(struct dirent *entry, char *path);
int						ft_lstsize_token(t_token *head);

// Expansion
char					*expand_variable(const char *variable);
void					append_variable_expanded(char **expanded,
							const char **cursor);
void					append_char_expanded(char **expanded,
							const char **cursor);
void					expand_token(t_token *token);
void					expand_variables_tokens(t_token *head);

#endif
