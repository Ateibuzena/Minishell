CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Lista de fuentes
SRC_DIR = ./src
SRCS = $(SRC_DIR)/d_ascii/ft_isspace.c $(SRC_DIR)/d_ascii/ft_isalpha.c \
       $(SRC_DIR)/d_ascii/ft_isdigit.c $(SRC_DIR)/d_ascii/ft_isalnum.c \
       $(SRC_DIR)/d_ascii/ft_isascii.c $(SRC_DIR)/d_ascii/ft_isprint.c \
       $(SRC_DIR)/d_ascii/ft_toupper.c $(SRC_DIR)/d_ascii/ft_tolower.c \
       $(SRC_DIR)/d_memory/ft_calloc.c $(SRC_DIR)/d_memory/ft_memset.c \
       $(SRC_DIR)/d_memory/ft_bzero.c $(SRC_DIR)/d_memory/ft_memcpy.c \
       $(SRC_DIR)/d_memory/ft_memmove.c $(SRC_DIR)/d_memory/ft_memchr.c \
       $(SRC_DIR)/d_memory/ft_memcmp.c \
       $(SRC_DIR)/d_strings/ft_strtol.c $(SRC_DIR)/d_strings/ft_strncpy.c \
       $(SRC_DIR)/d_strings/ft_strcmp.c $(SRC_DIR)/d_strings/ft_strlen.c \
       $(SRC_DIR)/d_strings/ft_strlcpy.c $(SRC_DIR)/d_strings/ft_strlcat.c \
       $(SRC_DIR)/d_strings/ft_strchr.c $(SRC_DIR)/d_strings/ft_strrchr.c \
       $(SRC_DIR)/d_strings/ft_strncmp.c $(SRC_DIR)/d_strings/ft_strnstr.c \
       $(SRC_DIR)/d_strings/ft_strmapi.c $(SRC_DIR)/d_strings/ft_striteri.c \
       $(SRC_DIR)/d_strings/ft_strdup.c $(SRC_DIR)/d_strings/ft_substr.c \
       $(SRC_DIR)/d_strings/ft_strjoin.c $(SRC_DIR)/d_strings/ft_strtrim.c \
       $(SRC_DIR)/d_strings/ft_strndup.c $(SRC_DIR)/d_strings/ft_strstr.c \
       $(SRC_DIR)/d_strings/ft_strcat.c $(SRC_DIR)/d_strings/ft_strcpy.c \
       $(SRC_DIR)/d_fds/ft_putchar_fd.c $(SRC_DIR)/d_fds/ft_putstr_fd.c \
       $(SRC_DIR)/d_fds/ft_putendl_fd.c $(SRC_DIR)/d_fds/ft_putnbr_fd.c \
       $(SRC_DIR)/d_get_next_line/get_next_line_utils.c \
       $(SRC_DIR)/d_get_next_line/get_next_line_utils_bonus.c \
       $(SRC_DIR)/d_get_next_line/get_next_line.c \
       $(SRC_DIR)/d_get_next_line/get_next_line_bonus.c \
       $(SRC_DIR)/d_printf/ft_puthex_lower.c $(SRC_DIR)/d_printf/ft_putnbr_u.c \
       $(SRC_DIR)/d_printf/ft_puthex_nil.c $(SRC_DIR)/d_printf/ft_putstr_printf.c \
       $(SRC_DIR)/d_printf/ft_putchar_percent.c $(SRC_DIR)/d_printf/ft_puthex_upper.c \
       $(SRC_DIR)/d_printf/ft_putchar_printf.c $(SRC_DIR)/d_printf/ft_putnbr_printf.c \
       $(SRC_DIR)/ft_split.c $(SRC_DIR)/ft_strlen_double.c $(SRC_DIR)/ft_atoi.c $(SRC_DIR)/ft_itoa.c \
       $(SRC_DIR)/ft_printf.c $(SRC_DIR)/ft_freedouble.c \
       $(SRC_DIR)/d_lists/ft_lstnew.c $(SRC_DIR)/d_lists/ft_lstadd_front.c \
       $(SRC_DIR)/d_lists/ft_lstsize.c $(SRC_DIR)/d_lists/ft_lstlast.c \
       $(SRC_DIR)/d_lists/ft_lstadd_back.c $(SRC_DIR)/d_lists/ft_lstdelone.c \
       $(SRC_DIR)/d_lists/ft_lstclear.c $(SRC_DIR)/d_lists/ft_lstiter.c \
       $(SRC_DIR)/d_lists/ft_lstmap.c

OBJ_DIR = ./obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME = libft.a

# Colors
RED     			= \033[0;31m
GREEN   			= \033[0;32m
YELLOW  			= \033[0;33m
CYAN    			= \033[0;36m
WHITE   			= \033[0;37m
RESET   			= \033[0m

# Reglas
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@printf "$(CYAN)[Building Main] Creating $(NAME)...\n$(RESET)"
	@ar rcs $(NAME) $(OBJS)
	@printf "$(GREEN)[Success] $(NAME) created successfully!\n$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)[Compiling]$(RESET) $<\n"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@printf "$(CYAN)[Directory] Creating object directory $(OBJ_DIR)...\n$(RESET)"
	@mkdir -p $(OBJ_DIR)

clean:
	@printf "$(RED)[Cleaning] Removing object files...\n$(RESET)"
	@rm -rf $(OBJ_DIR)
	@printf "$(GREEN)[Cleaned] Object files removed successfully!\n$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@printf "$(GREEN)[Cleaned] All binaries and libraries removed successfully!\n$(RESET)"

re: fclean all

.PHONY: all clean fclean re
