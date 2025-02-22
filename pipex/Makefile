CC = clang
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I$(LIBFT_DIR)

SRC_DIR = ./src
SRCS = $(SRC_DIR)/pipex_execute.c\
		$(SRC_DIR)/pipex_process.c\
		$(SRC_DIR)/pipex_utils.c\
		$(SRC_DIR)/pipex_init.c\
		$(SRC_DIR)/pipex_error.c\
		$(SRC_DIR)/pipex.c

OBJ_DIR = ./obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME = pipex.a

LIBS = -lreadline -lncurses

# Colors
RED     			= \033[0;31m
GREEN   			= \033[0;32m
YELLOW  			= \033[0;33m
CYAN    			= \033[0;36m
WHITE   			= \033[0;37m
RESET   			= \033[0m

# Reglas
all: $(LIBFT) $(NAME)

# Compilación de pipex solo si es necesario
$(NAME): $(OBJ_DIR) $(OBJS)
	@if [ ! -f $(NAME) ] || [ $(OBJS) -nt $(NAME) ]; then \
		printf "$(CYAN)[Building Pipex] Creating $(NAME)...\n$(RESET)"; \
		ar rcs $(NAME) $(OBJS); \
		printf "$(GREEN)[Success] $(NAME) created successfully!\n$(RESET)"; \
	else \
		printf "$(YELLOW)[Up-to-date] No recompilation needed for $(NAME).\n$(RESET)"; \
	fi

# Compilación de objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)[Compiling]$(RESET) $<\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Crear directorio de objetos si no existe
$(OBJ_DIR):
	@printf "$(CYAN)[Directory] Creating object directory $(OBJ_DIR)...\n$(RESET)"
	@mkdir -p $(OBJ_DIR)

# Compilar libft si es necesario
$(LIBFT):
	@printf "$(CYAN)[Building Libft] Compiling libft...\n$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@printf "$(GREEN)[Libft Ready] Libft compiled successfully!\n$(RESET)"

# Limpiar objetos
clean:
	@printf "$(RED)[Cleaning] Removing object files...\n$(RESET)"
	@rm -rf $(OBJ_DIR)
	@printf "$(GREEN)[Cleaned] Object files removed successfully!\n$(RESET)"

# Limpiar objetos y la biblioteca
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@printf "$(GREEN)[Cleaned] All binaries and libraries removed successfully!\n$(RESET)"

# Recompilación completa
re: fclean all

.PHONY: all clean fclean re
