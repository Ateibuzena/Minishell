CC = clang
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I$(LIBFT_DIR)

SRC_DIR = ./src
SRCS = $(SRC_DIR)/builtins_cd.c\
		$(SRC_DIR)/builtins_clear.c\
		$(SRC_DIR)/builtins_echo.c\
		$(SRC_DIR)/builtins_pwd.c\
		$(SRC_DIR)/builtins_env.c\
		$(SRC_DIR)/builtins_exit.c\
		$(SRC_DIR)/builtins_unset.c\
		$(SRC_DIR)/builtins_export.c\
		$(SRC_DIR)/executor.c\
		$(SRC_DIR)/ft_strtok.c

OBJ_DIR = ./obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME = builtins.a

LIBS = -lreadline -lncurses

# Colors
RED     			= \033[0;31m
GREEN   			= \033[0;32m
YELLOW  			= \033[0;33m
CYAN    			= \033[0;36m
WHITE   			= \033[0;37m
RESET   			= \033[0m

# Reglas
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
	@printf "$(CYAN)[Building Main] Creating $(NAME)...\n$(RESET)"
	@ar rcs $(NAME) $(OBJS)
	@printf "$(GREEN)[Success] $(NAME) created successfully!\n$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)[Compiling]$(RESET) $<\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@printf "$(CYAN)[Directory] Creating object directory $(OBJ_DIR)...\n$(RESET)"
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@printf "$(CYAN)[Building Libft] Compiling libft...\n$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@printf "$(GREEN)[Libft Ready] Libft compiled successfully!\n$(RESET)"

clean:
	@printf "$(RED)[Cleaning] Removing object files...\n$(RESET)"
	@rm -rf $(OBJ_DIR)
	@printf "$(GREEN)[Cleaned] Object files removed successfully!\n$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@printf "$(GREEN)[Cleaned] All binaries and libraries removed successfully!\n$(RESET)"

re: fclean all

.PHONY: all clean fclean re
