# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

HISTORY_DIR = ./history
HISTORY_LIB = $(HISTORY_DIR)/history.a

BUILTINS_DIR = ./builtins
BUILTINS_LIB = $(BUILTINS_DIR)/builtins.a

INCLUDES = -I$(LIBFT_DIR) -I$(HISTORY_DIR) -I$(BUILTINS_DIR)  # Incluye la nueva carpeta history

SRC_DIR = ./src
# Archivos fuente del proyecto principal
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/parser.c \
       $(SRC_DIR)/executor.c \
       $(SRC_DIR)/builtins.c \
       $(SRC_DIR)/signals.c \

OBJ_DIR = ./obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME = minishell

# Colors
RED      = \033[0;31m
GREEN    = \033[0;32m
YELLOW   = \033[0;33m
CYAN     = \033[0;36m
RESET    = \033[0m

# Reglas
all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT) $(HISTORY_LIB) $(BUILTINS_LIB) $(OBJS)
	@printf "$(CYAN)[Building Main] Creating $(NAME)...\n$(RESET)"
	@$(CC) $(OBJS) $(HISTORY_LIB) $(BUILTINS_LIB) $(LIBFT) -o $(NAME) -lreadline -lncurses
	@printf "$(GREEN)[Success] $(NAME) created successfully!\n$(RESET)"

# Combinación para crear los objetos (.o) en las carpetas correspondientes
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)  # Crea la estructura de directorios en obj
	@printf "$(YELLOW)[Compiling]$(RESET) $<\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@printf "$(CYAN)[Directory] Creating object directory $(OBJ_DIR)...\n$(RESET)"
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@printf "$(CYAN)[Building Libft] Compiling libft...\n$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@printf "$(GREEN)[Libft Ready] Libft compiled successfully!\n$(RESET)"

$(HISTORY_LIB):
	@printf "$(CYAN)[Building History] Compiling history.a...\n$(RESET)"
	@$(MAKE) -C $(HISTORY_DIR)
	@printf "$(GREEN)[History Ready] History library compiled successfully!\n$(RESET)"

$(BUILTINS_LIB):
	@printf "$(CYAN)[Building Builtins] Compiling builtins.a...\n$(RESET)"
	@$(MAKE) -C $(BUILTINS_DIR)
	@printf "$(GREEN)[Builtins Ready] Builtins library compiled successfully!\n$(RESET)"

clean:
	@printf "$(RED)[Cleaning] Removing object files...\n$(RESET)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(HISTORY_DIR) clean
	@$(MAKE) -C $(BUILTINS_DIR) clean
	@printf "$(GREEN)[Cleaned] Object files removed successfully!\n$(RESET)"

fclean: clean
	@printf "$(RED)[Full Clean] Removing binaries and libraries...\n$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(HISTORY_DIR) fclean
	@$(MAKE) -C $(BUILTINS_DIR) fclean
	@rm -f $(NAME)
	@printf "$(GREEN)[Cleaned] All binaries and libraries removed successfully!\n$(RESET)"

re: fclean all

.PHONY: all clean fclean re
