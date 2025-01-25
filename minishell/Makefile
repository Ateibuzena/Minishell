# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

HISTORY_DIR = ../history
HISTORY_LIB = $(HISTORY_DIR)/history.a

ENVIROMENT_DIR = ../enviroment
ENVIROMENT_LIB = $(ENVIROMENT_DIR)/enviroment.a

TOKENS_DIR = ../tokens
TOKENS_LIB = $(TOKENS_DIR)/tokens.a

BUILTINS_DIR = ../builtins
BUILTINS_LIB = $(BUILTINS_DIR)/builtins.a

PIPEX_DIR = ../pipex
PIPEX_LIB = $(PIPEX_DIR)/pipex.a

PROMPT_DIR = ../prompt
PROMPT_LIB = $(PROMPT_DIR)/prompt.a

INCLUDES = -I$(LIBFT_DIR) -I$(HISTORY_DIR) -I$(BUILTINS_DIR) -I$(TOKENS_DIR) -I$(ENVIROMENT_DIR) -I$(PROMPT_DIR) -I$(PIPEX_DIR)

SRC_DIR = ./src
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/executor.c \
	   $(SRC_DIR)/minishell_utils.c \
       $(SRC_DIR)/signals.c

OBJ_DIR = ./obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME = minishell

# Colors
RED      = \033[0;31m
GREEN    = \033[0;32m
YELLOW   = \033[0;33m
CYAN     = \033[0;36m
RESET    = \033[0m

all: $(NAME)

$(NAME): $(OBJ_DIR) $(PIPEX_LIB) $(PROMPT_LIB) $(TOKENS_LIB) $(BUILTINS_LIB) $(ENVIROMENT_LIB) $(HISTORY_LIB) $(LIBFT) $(OBJS)
	@printf "$(CYAN)[Building Main] Creating $(NAME)...\n$(RESET)"
	@$(CC) $(OBJS) $(PIPEX_LIB) $(PROMPT_LIB) $(TOKENS_LIB) $(BUILTINS_LIB) $(ENVIROMENT_LIB) $(HISTORY_LIB) $(LIBFT) -o $(NAME) -lreadline -lncurses
	@printf "$(GREEN)[Success] $(NAME) created successfully!\n$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)[Compiling]$(RESET) $<\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@printf "$(CYAN)[Directory] Creating object directory $(OBJ_DIR)...\n$(RESET)"
	@mkdir -p $(OBJ_DIR)

$(PIPEX_LIB):
	@printf "$(CYAN)[Building Pipex] Compiling pipex.a...\n$(RESET)"
	@$(MAKE) -C $(PIPEX_DIR)
	@printf "$(GREEN)[Pipex Ready] Pipex library compiled successfully!\n$(RESET)"

$(PROMPT_LIB):
	@printf "$(CYAN)[Building Prompt] Compiling prompt.a...\n$(RESET)"
	@$(MAKE) -C $(PROMPT_DIR)
	@printf "$(GREEN)[Prompt Ready] Prompt library compiled successfully!\n$(RESET)"

$(TOKENS_LIB):
	@printf "$(CYAN)[Building Builtins] Compiling tokens.a...\n$(RESET)"
	@$(MAKE) -C $(TOKENS_DIR)
	@printf "$(GREEN)[Builtins Ready] Tokens library compiled successfully!\n$(RESET)"

$(BUILTINS_LIB):
	@printf "$(CYAN)[Building Builtins] Compiling builtins.a...\n$(RESET)"
	@$(MAKE) -C $(BUILTINS_DIR)
	@printf "$(GREEN)[Builtins Ready] Builtins library compiled successfully!\n$(RESET)"

$(ENVIROMENT_LIB):
	@printf "$(CYAN)[Building Enviroment] Compiling enviroment.a...\n$(RESET)"
	@$(MAKE) -C $(ENVIROMENT_DIR)
	@printf "$(GREEN)[Enviroment Ready] Enviroment library compiled successfully!\n$(RESET)"

$(HISTORY_LIB):
	@printf "$(CYAN)[Building History] Compiling history.a...\n$(RESET)"
	@$(MAKE) -C $(HISTORY_DIR)
	@printf "$(GREEN)[History Ready] History library compiled successfully!\n$(RESET)"

$(LIBFT):
	@printf "$(CYAN)[Building Libft] Compiling libft.a...\n$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@printf "$(GREEN)[Libft Ready] Libft compiled successfully!\n$(RESET)"

clean:
	@printf "$(RED)[Cleaning] Removing object files...\n$(RESET)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(HISTORY_DIR) clean
	@$(MAKE) -C $(BUILTINS_DIR) clean
	@$(MAKE) -C $(TOKENS_DIR) clean
	@$(MAKE) -C $(ENVIROMENT_DIR) clean
	@$(MAKE) -C $(PROMPT_DIR) clean
	@$(MAKE) -C $(PIPEX_DIR) clean
	@printf "$(GREEN)[Cleaned] Object files removed successfully!\n$(RESET)"

fclean: clean
	@printf "$(RED)[Full Clean] Removing binaries and libraries...\n$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(HISTORY_DIR) fclean
	@$(MAKE) -C $(BUILTINS_DIR) fclean
	@$(MAKE) -C $(TOKENS_DIR) fclean
	@$(MAKE) -C $(ENVIROMENT_DIR) fclean
	@$(MAKE) -C $(PROMPT_DIR) fclean
	@$(MAKE) -C $(PIPEX_DIR) fclean
	@rm -f $(NAME)
	@printf "$(GREEN)[Cleaned] All binaries and libraries removed successfully!\n$(RESET)"

re: fclean all

.PHONY: all clean fclean re
