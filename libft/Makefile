# Library name
NAME = libft.a

# Compiler and compilation options
CC = cc
CFLAGS = -Wall -Werror -Wextra -fPIC -fPIE

# Sources
SRCS = src/d_ascii/ft_isspace.c src/d_ascii/ft_isalpha.c src/d_ascii/ft_isdigit.c src/d_ascii/ft_isalnum.c src/d_ascii/ft_isascii.c src/d_ascii/ft_isprint.c src/d_ascii/ft_toupper.c src/d_ascii/ft_tolower.c\
	src/d_memory/ft_calloc.c src/d_memory/ft_memset.c src/d_memory/ft_bzero.c src/d_memory/ft_memcpy.c src/d_memory/ft_memmove.c src/d_memory/ft_memchr.c src/d_memory/ft_memcmp.c\
	src/d_strings/ft_strtol.c src/d_strings/ft_strncpy.c src/d_strings/ft_strcmp.c src/d_strings/ft_strlen.c src/d_strings/ft_strlcpy.c src/d_strings/ft_strlcat.c  src/d_strings/ft_strchr.c src/d_strings/ft_strrchr.c src/d_strings/ft_strncmp.c src/d_strings/ft_strnstr.c src/d_strings/ft_strmapi.c src/d_strings/ft_striteri.c src/d_strings/ft_strdup.c src/d_strings/ft_substr.c src/d_strings/ft_strjoin.c src/d_strings/ft_strtrim.c\
	src/ft_split.c src/ft_strlen_double.c src/ft_atoi.c src/ft_itoa.c  src/ft_printf.c src/ft_freedouble.c\
	src/d_fds/ft_putchar_fd.c src/d_fds/ft_putstr_fd.c src/d_fds/ft_putendl_fd.c src/d_fds/ft_putnbr_fd.c\
	src/d_get_next_line/get_next_line_utils.c src/d_get_next_line/get_next_line_utils_bonus.c src/d_get_next_line/get_next_line.c src/d_get_next_line/get_next_line_bonus.c\
	src/d_printf/ft_puthex_lower.c src/d_printf/ft_putnbr_u.c src/d_printf/ft_puthex_nil.c src/d_printf/ft_putstr_printf.c src/d_printf/ft_putchar_percent.c src/d_printf/ft_puthex_upper.c src/d_printf/ft_putchar_printf.c src/d_printf/ft_putnbr_printf.c\

SRCS_BONUS = src/d_lists/ft_lstnew.c src/d_lists/ft_lstadd_front.c src/d_lists/ft_lstsize.c src/d_lists/ft_lstlast.c\
			src/d_lists/ft_lstadd_back.c src/d_lists/ft_lstdelone.c src/d_lists/ft_lstclear.c src/d_lists/ft_lstiter.c\
			src/d_lists/ft_lstmap.c\

# Header
HEADER = libft.h

# Colors
RED     			= \033[0;31m
GREEN   			= \033[0;32m
YELLOW  			= \033[0;33m
CYAN    			= \033[0;36m
WHITE   			= \033[0;37m
RESET   			= \033[0m

# Objects generated during compilation
OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

# Default rule for compiling the library
all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	@printf "$(CYAN)[Building Library]$(RESET) $(YELLOW)$(NAME)$(RESET)\n"
	@ar rcs $(NAME) $(OBJS)
	@printf "$(GREEN)[Success] $(NAME) created successfully!\n$(RESET)"

bonus: $(OBJS_BONUS) $(HEADER)
	@printf "$(CYAN)[Adding Bonus] Compiling bonus files...\n$(RESET)"
	@ar rcs $(NAME) $(OBJS_BONUS)
	@printf "$(GREEN)[Success] Bonus objects added to $(NAME)!\n$(RESET)"

%.o: %.c
	@printf "$(YELLOW)[Compiling]$(RESET) $<\n"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(RED)[Cleaning] Removing object files...\n$(RESET)"
	@rm -f $(OBJS) $(OBJS_BONUS)
	@printf "$(GREEN)[Cleaned] Object files removed successfully!\n$(RESET)"

fclean: clean
	@printf "$(RED)[Full Clean] Removing $(NAME)...\n$(RESET)"
	@rm -f $(NAME)
	@printf "$(GREEN)[Cleaned] $(NAME) removed successfully!\n$(RESET)"

re: fclean all

.PHONY: clean fclean all re bonus
