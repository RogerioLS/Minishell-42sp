/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 16:52:11 by roglopes          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/08/18 16:26:15 by roglopes         ###   ########.fr       */
=======
/*   Updated: 2024/07/31 00:23:03 by codespace        ###   ########.fr       */
>>>>>>> a0574562d2f366ec7808fec85f06cdd2b74cf9c6
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "../../libft/include/get_next_line.h"
# include "../../libft/include/libft.h"
# include "../../libft/include/ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <termios.h>

typedef enum e_tokens		t_tokens;
enum						e_tokens
{
	DTOKEN = -3,
	CMD_TOKEN = -2,
	FTOKEN = -1,
	NONE = 0,
	WORD,
	EXPANSION,
	GREAT,
	DGREAT,
	LESS,
	DLESS,
	PIPE,
};

typedef enum e_tree_typed	t_types_tree;
enum						e_tree_typed
{
	STRING = 10,
	DELIMITER,
	FILENAME,
	COMMAND,
	OUTPUT,
	APPEND,
	INPUT,
	HERE_DOC,
	PIPE_LINE,
};

typedef enum e_return		t_returned;
enum						e_return
{
	END = 666,
	ERROR = -1,
	FALSE = 0,
	TRUE = 1,
};

typedef enum e_fside		t_sided;
enum						e_fside
{
	LEFT = 0,
	RIGHT,
};

typedef enum e_check		t_check;
enum						e_check
{
	NFOUND = -2,
	SUCESS = 0,
	FAILED = 1,
};

typedef struct s_token		t_token;
struct						s_token
{
	char					*content;
	t_tokens				token;
	t_token					*next;
	t_token					*prev;
};

typedef struct s_tree		t_tree;
struct						s_tree
{
	char					*content;
	t_types_tree			tree_type;
	t_token					*left_token;
	t_token					*right_token;
	t_tree					*left;
	t_tree					*right;
};

typedef struct s_venv		t_venv;
struct						s_venv
{
	char					*key;
	char					*value;
	t_venv					*next;
};

typedef struct s_cmd		t_cmd;
struct						s_cmd
{
	char					*flagpath;
	char					**executed;
};

typedef struct s_data		t_data;
struct						s_data
{
	t_token					*token_list;
	t_tree					*tree_listed;
	t_venv					*envp;
	int						endsts;
	int						attribute;
	int						has_env;
	int						direction;
	int						pipe_fd[2];
	pid_t					fork[2];

};

extern volatile int			g_vsig;
/**
 * @brief Inicialização e Sinais
 * 
 * init_minihell: Inicializa o MiniShell com as variáveis de ambiente 
 * e o comando de entrada, retornando o status da execução.
 * inside_heredoc: Verifica ou define se o shell está dentro 
 * de um heredoc.
 * sig_newline: Manipulador de sinal para imprimir uma nova linha
 * em resposta a um sinal.
 * handle_signal: Manipula sinais recebidos pelo shell, como SIGINT ou SIGQUIT.
 * init_signals: Inicializa os sinais usados pelo MiniShell.
 */
int							init_minihell(t_venv **envp, char *input,
								int status);
int							inside_heredoc(int inside_heredoc);
void						sig_newline(int signum);
void						handle_signal(int signum);
void						init_signals(void);

/**
 * @brief Manipulação de Strings e Tokens
 * 
 * ft_strndup: Duplica uma string com tamanho limitado.
 * build_token: Constrói uma lista de tokens a partir da
 * linha de comando fornecida.
 * create_redirect_token: Cria um token de redirecionamento baseado 
 * na linha de comando e no caractere fornecido.
 * create_quote_token: Cria um token de citação a partir da linha de comando.
 * find_cmdtoken: Encontra o token de comando na lista de tokens.
 * relink_tokens: Reorganiza tokens dentro da lista de tokens, 
 * geralmente após a manipulação de redirecionamentos.
 * build_redirect_token: Constrói um token de redirecionamento na lista de tokens.
 * token_lstnew: Cria um novo token na lista.
 * token_lstadd_back: Adiciona um token ao final da lista de tokens.
 * token_lstlast: Retorna o último token da lista.
 * tokenlst_clear: Limpa a lista de tokens, liberando a memória.
 * manage_all_ttypes: Gerencia todos os tipos de tokens na lista de 
 * tokens e os dados associados.
 * manage_tlists: Gerencia listas de tokens dentro da estrutura de dados.
 * manage_evar: Gerencia variáveis de ambiente associadas aos tokens.
 * reorganize_redirect_tokens: Reorganiza tokens de redirecionamento
 * dentro da lista de tokens.
 * parse_created_tokens: Faz o parsing dos tokens criados a 
 * partir da linha de comando, considerando citações.
 * env_searched: Procura por uma chave de variável de ambiente
 * e a associa à linha final processada.
 * evarjoin: Junta partes de uma variável de ambiente processada na linha final.
 * concat_word: Concatena palavras em uma string, lidando com aspas simples.
 * fix_envtoken: Ajusta tokens de ambiente na lista final processada.
 * reorganize_tokens: Reorganiza a lista de tokens para facilitar a execução.
 */
char						*ft_strndup(const char *src, int size);
int							build_token(char *cmd_line, t_token **token_list);
t_token						*create_redirect_token(int *i, char *cmd_line,
								char c);
void						create_quote_token(char *cmd_line, int *size);
t_token						*find_cmdtoken(t_token *current);
void						relink_tokens(t_token *target, t_token *first_cmd,
								t_token *last_cmd,
								t_token *input);
t_token						*build_redirect_token(int *i, char *cmd_line);
t_token						*token_lstnew(char *content, t_tokens type);
void						token_lstadd_back(t_token **lst, t_token *new);
t_token						*token_lstlast(t_token *lst);
void						tokenlst_clear(t_token **lst);
t_token						*manage_all_ttypes(t_token *current,
								int *has_operator, t_data *data,
								t_venv **envp);
t_token						*manage_tlists(t_data *data, t_venv **envp);
t_token						*manage_evar(t_token *token, t_venv **envp,
								t_data *data);
t_token						*reorganize_redirect_tokens(t_token *stm);
int							parse_created_tokens(char *cmd_line, int *size,
								int has_quote);
void						env_searched(char *env_key,
								char **final_line, t_venv **envp);
char						*evarjoin(int *i, char *content,
								char **final_line, t_data *data);
void						concat_word(int *i, char *content,
								char **final_line, int has_single_quote);
t_token						*fix_envtoken(t_token *token,
								char **final_line, t_data *data);
t_token						*reorganize_tokens(t_token **token_list);

/**
 * @brief Árvores Sintáticas
 * 
 * eotokens: Cria uma árvore sintática a partir de uma lista de tokens.
 * tree_addright: Adiciona um novo nó à direita na árvore sintática.
 * tree_addleft: Adiciona um novo nó à esquerda na árvore sintática.
 * tree_new: Cria um novo nó na árvore sintática.
 * treelst_clear: Limpa a árvore sintática, liberando a memória.
 * build_tnode: Constrói um nó na árvore sintática a partir de um token.
 * type_check: Verifica o tipo de um token na árvore.
 * has_left_cmds: Verifica se há comandos à esquerda de um nó na árvore.
 * has_right_cmds: Verifica se há comandos à direita de um nó na árvore.
 * cut_all: Corta e organiza a árvore sintática.
 * cut_tleft: Realiza operações de corte à esquerda na árvore.
 * cut_tright: Realiza operações de corte à direita na árvore.
 * 
 */
void						eotokens(t_token **token_list,
								t_tree **tree_listed);
void						tree_addright(t_tree **lst, t_tree *new);
void						tree_addleft(t_tree **lst, t_tree *new);
t_tree						*tree_new(char *content, t_tokens type);
void						treelst_clear(t_tree **lst);
void						build_tnode(t_token *new_node,
								t_tree **tree_listed, int direction);
t_types_tree				type_check(t_tokens token);
void						has_left_cmds(t_tree *node,
								t_tree *current_tnode);
void						has_right_cmds(t_tree *node,
								t_tree *current_tnode);
t_tree						*cut_all(t_token *current, t_tree **tree_listed,
								int state);
void						cut_tleft(t_tokens opr,
								t_tree *current_node_in, t_tree **tree_listed,
								int status);
void						cut_tright(t_tokens opr,
								t_tree *current_node_in, t_tree **tree_listed,
								int status);

/**
 * @brief Built-ins e Execução de Comandos
 * 
 * init_builtins: Inicializa e chama os comandos built-in (como cd, echo, etc.).
 * call_pwd: Executa o comando pwd, retornando o diretório atual.
 * ft_changedir: Executa o comando cd, alterando o diretório atual.
 * ft_clear: Executa o comando clear.
 * ft_echo: Executa o comando echo, imprimindo a entrada.
 * ft_env: Executa o comando env, listando as variáveis de ambiente.
 * ft_unset: Executa o comando unset, removendo uma variável de ambiente.
 * ft_exported_env: Executa o comando export, adicionando uma nova variável de ambiente.
 * ft_envprints: Imprime as variáveis de ambiente.
 * ongoing_exec: Executa comandos externos, gerenciando a árvore sintática.
 * initialize_trees: Inicializa a execução da árvore sintática.
 * get_cmd_args: Obtém os argumentos de comando a partir da árvore sintática.
 * get_path: Obtém o caminho de execução de um comando baseado na
 * árvore e nas variáveis de ambiente.
 * foundedcmd: Procura por comandos encontrados na árvore sintática.
 * rltree_redirect: Gerencia redirecionamentos na árvore sintática.
 * execute_command: Executa um comando a partir de um nó na árvore sintática.
 * execution_error: Lida com erros de execução de comando.
 * exit_minihell: Gerencia a saída do MiniShell, liberando recursos.
 * check_exit: Verifica se o comando é um comando de saída.
 * if_exited: Lida com o fluxo de execução após a saída de um comando.
 * execute_pipe: Executa comandos em um pipeline.
 * endpipes: Finaliza a execução de um pipeline.
 * executables_init: Inicializa a execução de binários executáveis.
 * 
 */
int							init_builtins(char **args, t_data *data,
								t_venv **envp);
int							call_pwd(char *input);
int							ft_changedir(char **input, t_venv **envp);
int							ft_clear(char *input);
int							ft_echo(char **arg, t_data *data);
int							ft_env(t_venv **envp, int status);
int							ft_unset(t_venv **head, char *key);
void						ft_exported_env(char *var, t_venv **envp);
int							ft_envprints(t_venv *env);
int							ongoing_exec(t_data *data, t_venv **envp);
int							initialize_trees(t_tree *node, t_data *data);
char						**get_cmd_args(t_tree *node, int direction);
char						**get_path(t_venv **envp, char *var, char *cmd);
t_tree						*foundedcmd(t_tree **stm, int *count);
int							rltree_redirect(t_tree *node, \
								t_tree **cmd);
int							execute_command(t_tree *node, t_data *data,
								t_venv **envp, int direction);
int							execution_error(char **cmd_args, t_venv **envp,
								int status);
int							exit_minihell(t_data *data,
								t_venv **envp, char **cmd_args);
int							check_exit(char *input);
char						**if_exited(t_tree *node, int direction);
int							execute_pipe(t_tree *opr, t_data *data);
int							endpipes(int *status, t_data *data);
int							executables_init(t_tree *node, t_data *data, \
								t_venv **envp);

/**
 * @brief Manipulação de Ambiente e Variáveis
 * 
 * env_lstnew: Cria uma nova variável de ambiente.
 * env_lstadd_back: Adiciona uma variável de ambiente ao final da lista.
 * env_lstclear: Limpa a lista de variáveis de ambiente.
 * env_lstsearch: Procura por uma variável de ambiente na lista.
 * env_size: Retorna o tamanho da lista de variáveis de ambiente.
 * get_envp: Inicializa a lista de variáveis de ambiente com as
 * variáveis fornecidas pelo sistema.
 * expand_env: Expande variáveis de ambiente em uma string.
 * 
 */
t_venv						*env_lstnew(char *key, char *value);
void						env_lstadd_back(t_venv **lst, t_venv *new);
void						env_lstclear(t_venv **lst);
t_venv						*env_lstsearch(t_venv **lst, char *key);
int							env_size(t_venv **env);
void						get_envp(t_venv **envp, char **environ);
char						*expand_env(char *content, t_venv **envp,
								t_data *data);

/**
 * @brief Redirecionamento e Heredoc
 * 
 * put_redirect_in: Configura o redirecionamento de entrada.
 * put_redirect_out: Configura o redirecionamento de saída.
 * append_redirects: Configura o redirecionamento para
 * anexar a arquivos.
 * execute_heredoc: Executa o comando heredoc.
 * release_heredoc: Libera recursos associados ao heredoc.
 * vheredoc_quote: Verifica se há aspas no heredoc.
 * heredocwrite: Escreve o conteúdo do heredoc no arquivo associado.
 * founded_hd: Procura por um heredoc na árvore sintática.
 * here_doc_eof: Lida com o fim do arquivo para um heredoc.
 * 
 */
int							put_redirect_in(t_tree *opr);
int							put_redirect_out(t_tree *opr);
int							append_redirects(t_tree *opr);
int							execute_heredoc(t_tree *opr, t_data *data,
								t_venv **envp, int index);
int							release_heredoc(t_tree *opr);
int							vheredoc_quote(char *content);
void						heredocwrite(char *line, int fd_heredoc, \
								t_data *data, t_venv **envp);
int							founded_hd(t_tree *stm, t_data *data,
								t_venv **envp);
void						here_doc_eof(int line_num, char *content, \
								char *line);

/**
 * @brief Utilidades e Funções Auxiliares
 * 
 * all_checked: Verifica se a entrada contém apenas caracteres válidos.
 * has_pipe_in: Verifica se há um pipe na entrada.
 * fkclose: Fecha um descritor de arquivo com tratamento de erros.
 * free_trash: Libera memória de uma array de strings.
 * free_data: Libera memória associada à estrutura de dados.
 * free_envp: Libera memória associada às variáveis de ambiente.
 * free_args: Libera memória associada aos argumentos de comando.
 * arg_with_quote: Processa um argumento que contém aspas.
 * arg_just_word: Processa um argumento sem aspas.
 * release_quotes_expand: Remove aspas e expande variáveis de ambiente.
 * initialize: Inicializa o MiniShell e suas dependências.
 * 
 */
int							all_checked(const char *input);
int							has_pipe_in(const char *input);
void						fkclose(int *fd, char *error);
void						free_trash(char **trash);
void						free_data(t_data **data);
void						free_envp(t_venv **envp);
void						free_args(char **path_args, char **args);
char						*arg_with_quote(char *content);
char						*arg_just_word(char *content);
char						*release_quotes_expand(char *content);
void						initialize(void);
int							ft_strncmp(const char *s1,
								const char *s2, size_t n);
void						ft_putendl_fd(char *s, int fd);
char						*ft_strjoin(char const *s1, char const *s2);
int							execution_error(char **cmd_args,
								t_venv **envp, int status);

#endif
