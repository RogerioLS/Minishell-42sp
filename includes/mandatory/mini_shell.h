/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:04:17 by codespace         #+#    #+#             */
/*   Updated: 2024/09/23 20:37:00 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "../libft/libft.h"
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

# define INVALID_QUOTE "Invalid syntax,check for open quotes or brackets.\n"

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
	PIPE = 1,
	OPEN_PAREN,
	CLOSE_PAREN,
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
void						ft_set_env(char *new_str, char *key, char *value);
char						*ft_strdup_calloc(const char *s);
void						ft_close_pipe(int *pipe_fd);
char						*ft_strchr_quote_aware(const char *s, int c);
void						ft_init_environ(void);
void						initialize(void);

// run_minishell
int							ft_finish_program(int status);
void						ft_reset_mini(char *line);
void						ft_terminal_properties(void);
char						*ft_init_and_wait_input(t_token **list);

// free
void						ft_free_env(void);

// utilis error
int							ft_signal_error(void);
int							throw_error(char *cmd_path);
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
int							ft_setup_fork_signal_handlers(int pid);

// lexer
int							ft_lexer(char *input, t_token **tokens);
int							ft_check_syntax_input(char *input);
void						ft_move_to_next_quote(char *input, int *index,
								int *single_quote, int *double_quote);
int							ft_get_token_type(char *input);
int							ft_get_token_length(char *imput, int type);
int							ft_get_word_length(char *input);

// parser
int							ft_parser(t_token *list, t_tree_node **root);
int							ft_check_syntax(t_token *current);
int							ft_check_control_operator_rule(t_token *token);
int							ft_check_redirect_rule(t_token *token);

// bin tree
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

// token
t_token						*ft_token_lst_new(char *value, int token_type);
void						ft_token_lst_add_back(t_token **token_list,
								t_token *new);
int							ft_token_lst_get_size(t_token *token_list);
t_token						*ft_token_lst_get_last(t_token *token_list);
void						ft_sort_token_lst(t_token **head);

// ft_executor
int							ft_execute_command(t_tree_node *token_node);
char						**ft_get_cmd_and_args(t_token *cmd);
int							ft_execute_pipe(t_tree_node *left, \
							t_tree_node *right);
void						ft_wait_child_status(pid_t pid, int *status);
int							ft_execute_redirect(t_tree_node *left,
								t_tree_node *right, int redir_type);
int							ft_executor(t_tree_node *root);

//expand
void						expand_tokens(t_tree_node *cmd_node);
char						*expand_vars(char *str);
char						*remove_quotes(char *str);
void						retokenize(t_token **token);
void						handle_empty_value(t_token **current,
								t_tree_node **cmd_node);

// builtins
bool						is_builtin(t_token *tokens);
int							execute_builtin(t_token *tokens);
int							ft_cd(t_token *tokens);
int							ft_echo(t_token *tokens);
int							ft_env(t_token *cmd);
int							ft_exit(t_token *tokens);
int							ft_export(t_token *tokens);
int							ft_pwd(void);
int							ft_unset(t_token *tokens);

char						*get_key(char *arg);
int							is_valid_identifier(char *str, char *cmd_name);
int							is_env_key_present(char *key);
int							is_key_without_value(char *key);

// heredoc
void						heredoc_signal_handler(int signum);
int							create_heredoc_file(t_token *token);
int							delete_heredoc_files(void);

#endif
