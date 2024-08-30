/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:35:36 by roglopes          #+#    #+#             */
/*   Updated: 2024/09/23 17:54:33 by ecoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "../../libft/include/ft_printf.h"
# include "../../libft/include/get_next_line.h"
# include "../../libft/include/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE 1
# define SYNTAX_ERROR 2

# define INVALID_QUOTE "Invalid syntax,check input for open quotes or brackets.\n"

typedef struct s_token		t_token;
struct						s_token
{
	int						type;
	char					*value;
	struct s_token			*prev;
	struct s_token			*next;
};

typedef struct s_tree_node	t_tree_node;
struct						s_tree_node
{
	t_token					*token;
	struct s_tree_node		*left;
	struct s_tree_node		*right;
};

typedef enum e_tokens		t_tokens;
enum						e_tokens
{
	AND = 1,
	OR,
	PIPE,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_IN,
	REDIR_OUT,
	SPACES,
	END,
	WORD,
};

// main
void						ft_print_welcome(void);

// free
void						ft_free_env(int i);
void						ft_free_memory(void);

// env
char						***get_my_env(void);
// utilis error
int							ft_signal_error(void);
int							ft_handle_error(char *message);
int							ft_syntax_error(char *token);
char						***ft_get_my_env(void);
int							*ft_get_exit_status(void);
int							ft_set_exit_status(int status);
char						*ft_substr(char const *s, unsigned int start,
								size_t len);

// signal
int							ft_setup_signal_handler(void (*func)(int signum));
void						ft_main_signal_handler(int signum);

// lexer
int							ft_lexer(char *input, t_token **tokens);
int							ft_check_syntax_input(char *input);
void						ft_move_to_next_quote(char *input, int *index,
								int *single_quote, int *double_quote);
int							ft_get_token_type(char *input);
int							ft_get_token_length(char *imput, int type);
int							ft_get_word_length(char *input);

// token
t_list						**ft_get_memory_lst(void);
void						ft_collect_mem(void *content);
void						*ft_dalloc(size_t nmemb, size_t size);
t_token						*ft_token_lst_new(char *value, int token_type);
void						ft_token_lst_add_back(t_token **token_list,
								t_token *new);
int							ft_token_lst_get_size(t_token *token_list);
t_token						*ft_token_lst_get_last(t_token *token_list);
void						ft_sort_token_lst(t_token **head);

// parser
int							ft_parser(t_token *list, t_tree_node **root);
int							ft_check_syntax(t_token *current);
int							ft_check_control_operator_rule(t_token *token);
int							ft_check_redirect_rule(t_token *token);
t_tree_node					*ft_build_execution_tree(t_token *token_list);
void						ft_split_tokens_into_tree(t_tree_node *tree_node,
								t_token *token_list);
void						ft_split_list(t_tree_node *tree_node,
								t_token *token_list, t_token *token_to_cut);
t_token						*ft_cut_token_list(t_token *token_list,
								t_token *token_to_cut);
void						ft_split_redirect(t_tree_node *tree_node,
								t_token *token_list, t_token *token_to_cut);
t_token						*ft_search_pipe(t_token *token_list);
t_token						*ft_search_redirect(t_token *token_list);
t_tree_node					*ft_get_redir_filename(t_token *redir);

// builtins
bool						is_builtin(t_token *tokens);
int							execute_builtin(t_token *tokens);
int							ft_cd(t_token *tokens);
int							ft_echo(t_token *tokens);
int							ft_env(t_token *cmd);
int							ft_exit(t_token *tokens);
// ----------- export --------------------
int							ft_export(t_token *tokens);
char						*get_key(char *arg);
int							is_valid_identifier(char *str, char *cmd_name);
int							is_env_key_present(char *key);
int							is_key_without_value(char *key);
int							ft_pwd(void);
int							ft_unset(t_token *tokens);

void						heredoc_signal_handler(int signum);
int							*get_exit_status(void);

#endif
