# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/31 16:34:27 by roglopes          #+#    #+#              #
#    Updated: 2024/04/13 19:05:45 by roglopes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell

SOURCES_DIR			= sources/
OBJECTS_DIR			= objects/

HEADERS				= -I ./includes/mandatory/ -I ./libft/include/

MAIN_DIR		= $(SOURCES_DIR)mandatory/main/
UTILS_DIR		= $(SOURCES_DIR)mandatory/utils/
VARIABLES_DIR	= $(SOURCES_DIR)mandatory/variables/
TOKEN_DIR	= $(SOURCES_DIR)mandatory/tokenizer/

LIBFT				= ./libft/libft.a

CFLAGS				= -Wextra -Wall -Werror -g3
CC					= cc

VALGRIND_LOG		= valgrind.log

MAIN_SOURCES	= $(MAIN_DIR)main.c

UTILS_SOURCES	= $(UTILS_DIR)utils.c \
			$(UTILS_DIR)utils2.c \

TOKEN_SOURCES	= $(TOKEN_DIR)tokenizer.c \
			$(TOKEN_DIR)create_token.c \

VARIABLES_SOURCES	= $(VARIABLES_DIR)exit_type.c \
					$(VARIABLES_DIR)line_var.c \
					$(VARIABLES_DIR)validates.c \

SOURCES				= $(MAIN_SOURCES) $(UTILS_SOURCES) $(VARIABLES_SOURCES) $(TOKEN_SOURCES) 

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
	@printf "$(GREEN)Compiling Push Swap %d%%\r$(RESET)" $$(echo $$(($(COUNT) * 100 / $(words $(SOURCES_DIR)))))

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
	@echo "$(CYAN)NORMINETTE OK $(RESET)"

valgrind: all
	@valgrind --leak-check=full \
	--show-reachable=yes \
	--show-leak-kinds=all -s \
	--track-origins=yes \
	--log-file=$(VALGRIND_LOG) \
	./$(NAME)
	@cat $(VALGRIND_LOG)

re: fclean all
	@echo "$(BLUE) $(NAME) Cleaned and rebuilt everything!"

.PHONY: all clean fclean re libft bonus norm create_objects_dir valgrind
