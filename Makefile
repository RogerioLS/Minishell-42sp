# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecoelho- <ecoelho-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/01 20:01:05 by codespace         #+#    #+#              #
#    Updated: 2024/09/23 18:03:36 by ecoelho-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= minishell

SOURCES_DIR			= sources/
OBJECTS_DIR			= objects/

HEADERS				= -I ./includes/mandatory/ -I ./libft

MAIN_DIR			= $(SOURCES_DIR)mandatory/main/
SIGNALS_DIR			= $(SOURCES_DIR)mandatory/signals/
LEXER_DIR			= $(SOURCES_DIR)mandatory/lexer/
INITIALIZE_DIR		= $(SOURCES_DIR)mandatory/initialize/
TOKEN_DIR			= $(SOURCES_DIR)mandatory/tokenizer/
PARSER_DIR			= $(SOURCES_DIR)mandatory/parser/
EXPANSION_DIR		= $(SOURCES_DIR)mandatory/expansion/
EXECUTOR_DIR		= $(SOURCES_DIR)mandatory/executor/
BUILTINS_DIR		= $(SOURCES_DIR)mandatory/builtins/
UTILS_DIR			= $(SOURCES_DIR)mandatory/utils/
FREE_DIR			= $(SOURCES_DIR)mandatory/free/
REDIRECT_DIR		= $(SOURCES_DIR)mandatory/redirect/

LIBFT				= ./libft/libft.a

CFLAGS				= -Wall -Wextra -Werror -g3
CC					= cc

VALGRIND_LOG		= valgrind.log

MAIN_SOURCES		= $(MAIN_DIR)main.c \
					$(MAIN_DIR)run_minishell.c \
					$(MAIN_DIR)welcome.c

SIGNALS_SOURCES		= $(SIGNALS_DIR)signal.c

LEXER_SOURCES		= $(LEXER_DIR)lexer.c \
					$(LEXER_DIR)check_syntax_input.c

INITIALIZE_SOURCES	= $(INITIALIZE_DIR)

TOKEN_SOURCES		= $(TOKEN_DIR)token_list.c

PARSER_SOURCES		= $(PARSER_DIR)parser.c \
					$(PARSER_DIR)bin_tree.c \
					$(PARSER_DIR)bin_tree_aux.c

EXPANSION_SOURCES	= $(EXPANSION_DIR)expand.c \
					$(EXPANSION_DIR)expand_utils.c

EXECUTOR_SOURCES	= $(EXECUTOR_DIR)executor.c \
					$(EXECUTOR_DIR)execute_redirect.c \
					$(EXECUTOR_DIR)execute_pipe.c \
					$(EXECUTOR_DIR)execute_command.c

BUILTINS_SOURCES	= $(BUILTINS_DIR)builtins.c \
					$(BUILTINS_DIR)cd.c \
					$(BUILTINS_DIR)echo.c \
					$(BUILTINS_DIR)env.c \
					$(BUILTINS_DIR)exit.c \
					$(BUILTINS_DIR)pwd.c \
					$(BUILTINS_DIR)unset.c \
					$(BUILTINS_DIR)export.c

UTILS_SOURCES		= $(UTILS_DIR)environ.c   \
					$(UTILS_DIR)error.c       \
					$(UTILS_DIR)builtins_utils.c   \
					$(UTILS_DIR)utils.c

FREE_SOURCES		= $(FREE_DIR)free.c

REDIRECT_SOURCES	= $(REDIRECT_DIR)heredoc.c

SOURCES				= $(MAIN_SOURCES) $(SIGNALS_SOURCES) $(FREE_SOURCES) \
					$(UTILS_SOURCES) $(LEXER_SOURCES) $(TOKEN_SOURCES) \
					$(PARSER_SOURCES) $(BUILTINS_SOURCES) $(EXECUTOR_SOURCES) \
					$(EXPANSION_SOURCES) $(REDIRECT_SOURCES)

OBJS				= $(patsubst $(SOURCES_DIR)%.c,$(OBJECTS_DIR)%.o, $(SOURCES))

COUNT				:= 0
RED					= \033[0;31m
GREEN				= \033[0;32m
MAGENTA				= \033[0;35m
RESET				= \033[0m
CYAN				= \033[36;1;3;208m
YELLOW				= \033[0;33m
COLOR_LIMITER		= "\033[0m"

all: create_objects_dir libft $(OBJECTS_DIR) $(NAME)

$(OBJECTS_DIR)%.o: $(SOURCES_DIR)%.c
	@mkdir -p $(@D)
	@$(eval COUNT=$(shell expr $(COUNT) + 1))
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	@printf "$(GREEN)Compiling Mini Hell %d%%\r$(RESET)" $$(echo $$(($(COUNT) * 100 / $(words $(SOURCES_DIR)))))

$(NAME): $(OBJS) 
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) $(LIBFT) -o $(NAME) -lreadline

create_objects_dir:
	@mkdir -p $(OBJECTS_DIR)

libft:
	@make -C ./libft --no-print-directory

clean:
	@make clean -C ./libft --no-print-directory
	@rm -rf $(OBJECTS_DIR)
	@rm -rf $(VALGRIND_LOG)
	@printf "$(RED)Deleted objects Mini Shell$(RESET)\n"

fclean: clean
	@echo "Cleaning all... 🧹"
	@rm -rf $(NAME)
	@make fclean -C ./libft --no-print-directory
	@printf "$(RED)Project is deleted Mini Shell$(RESET)\n"
	@printf "$(RED)File valgrind.log deleted$(RESET)\n"
	@echo "✨ Cleaning complete! ✨"

norm:
	@norminette -R CheckForbiddenSource
	@echo "$(CYAN)NORMINETTE SUCESS $(RESET)"

valgrind: re
	@valgrind --leak-check=full \
	--show-reachable=yes \
	--show-leak-kinds=all -s \
	--track-origins=yes \
	--suppressions=readline.supp \
	--log-file=$(VALGRIND_LOG) \
	./$(NAME)
	@cat $(VALGRIND_LOG)

re: fclean all
	@echo "$(BLUE) $(NAME) Cleaned and rebuilt everything!"

.PHONY: all clean fclean re libft bonus norm create_objects_dir valgrind
