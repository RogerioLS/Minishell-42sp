/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lluiz-de <lluiz-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:52:11 by roglopes          #+#    #+#             */
/*   Updated: 2024/04/14 01:21:01 by lluiz-de         ###   ########.fr       */
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

# define ARG_MAX 4096 // Máximo do próprio shell//

typedef struct s_mini
{
	char			*name;
	char			*cmd_line;
	int				exported;
	int				aftercmd;
	struct s_mini	*next;
}					t_mini;

typedef enum
{
	TOKEN_WORD,
	TOKEN_OPERATOR,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND_OUT
}					TokenType;

typedef struct Token
{
	char			*text;
	TokenType		type;
	struct Token	*next;
}					Token;

typedef struct Alias
{
	char			*name;
	char			*command;
	struct Alias	*next;
}					Alias;

typedef enum
{
	COMMAND_SIMPLE,
	COMMAND_PIPELINE,
	COMMAND_REDIRECTION_INPUT,
	COMMAND_REDIRECTION_OUTPUT,
	COMMAND_REDIRECTION_APPEND
}					CommandType;

typedef struct Command
{
	char			*text;
	CommandType		type;
	struct Command	*next;
}					Command;

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
void				freecommands(Command *head);
void				freetokens(Token *head);

// Tokenizer
Token				*create_token(const char *text, TokenType type);
Token				*tokenize_input(char *input);
void				iterate_tokens(char *input, Token **current);
bool				is_operator_char(char c);
bool				is_inside_quotes(char *cursor);
char				*skip_quotes(char *cursor);
bool				is_operator_or_end(char *cursor);

#endif
