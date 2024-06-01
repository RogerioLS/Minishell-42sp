/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:52:11 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/01 17:33:53 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "../../libft/include/ft_printf.h"
# include "../../libft/include/get_next_line.h"
# include "../../libft/include/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <grp.h>
# include <pwd.h>
# include <sys/stat.h>
# include <limits.h>
# include <errno.h> 

# define MAX_PATH_LEN 1024
# define ARG_MAX 4096 // Máximo do próprio shell//

enum e_token_type
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
	char			*name;
	char			*cmd_line;
	int				exported;
	int				aftercmd;
	struct s_mini	*next;
}					t_mini;

typedef struct s_token
{
	char				*text;
	enum e_token_type	type;
	struct s_token		*next;
}				t_token;

typedef struct s_alias
{
	char			*name;
	char			*command;
	struct s_alias	*next;
}			t_alias;

typedef enum
{
	COMMAND_SIMPLE,
	COMMAND_PIPELINE,
	COMMAND_REDIRECTION_INPUT,
	COMMAND_REDIRECTION_OUTPUT,
	COMMAND_REDIRECTION_APPEND
}				CommandType;

typedef struct s_command
{
	char			*text;
	CommandType		type;
	struct s_command	*next;
}			t_command;

// Utils
char				*ft_strtok(char *str, const char *delim);
char				*ft_antispace(char *buff);
char				*ft_firstword(char *buff);

// Utils2
size_t				ft_strcspn(const char *s, const char *reject);
size_t				ft_strspn(const char *s, const char *accept);

// Variables
int					ft_exit(char *buff);
bool				commandline_var(char *cmd);
bool				validate_name(char *var_name);

// Free
void				ft_free_commands(t_command *head);
void				ft_free_tokens(t_token *head);

// Tokenizer
t_token				*create_token(const char *text, enum e_token_type type);

t_token				*input_tokenizer(char *input);
//t_token			*tokenize_input(char *input);
// void				iterate_tokens(char *input, t_token **current);
bool				is_operator_char(char c);
bool				is_inside_quotes(char *cursor);
char				*skip_quotes(char *cursor);
bool				is_operator_or_end(char *cursor);
int					classify_token(const char *token);
char				**tokens_to_argv(t_token *tokens);

// Prompt
char				*prompt(void);
int					afterprompt(int is_after);

// Signal
void				handle_signal(int sign);

// Command
// void				execute_command(char **args, int argc);
void execute_command(char **args, int argc, int input_fd, int output_fd);
size_t				ft_arraylen(char **array);
void				export_variable(char **args);
void				ft_cd(char *path);
void				clear_screen(void);
// void				list_directory(char **args);
void				ft_pwd(int argc, char **argv);
void				print_environment(void);
void				process_arguments(char **args, char *path, int *long_format);
void 				ft_unset(char **args);
void 				ft_echo(char **args);
void 				ft_free_string_array(char **array);
char 				*ft_strjoin_free(char *s1, char *s2);

// Command Utils
char				*ft_strcpy(char *dest, const char *src);
void				process_arguments(char **args, char *path, int *long_format);
void				print_file_info(struct dirent *entry, char *path);
int					ft_lstsize_token(t_token *head);

// Expansion
char				*expand_variable(const char *variable);
void				append_variable_expanded(char **expanded, const char **cursor);
void				append_char_expanded(char **expanded, const char **cursor);
void				expand_token(t_token *token);
void				expand_variables_tokens(t_token *head);

#endif
