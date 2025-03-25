NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I. -I../pipex -I../tokens -I../prompt -I../builtins -I../enviroment -I../history -I../libft

RM = rm -f

# 📂 Librerías externas
LIBFT_DIR = ../libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

HISTORY_DIR = ../history
HISTORY_LIB = $(HISTORY_DIR)/history.a

ENVIROMENT_DIR = ../enviroment
ENVIROMENT_LIB = $(ENVIROMENT_DIR)/enviroment.a

BUILTINS_DIR = ../builtins
BUILTINS_LIB = $(BUILTINS_DIR)/builtins.a

PROMPT_DIR = ../prompt
PROMPT_LIB = $(PROMPT_DIR)/prompt.a

TOKENS_DIR = ../tokens
TOKENS_LIB = $(TOKENS_DIR)/tokens.a

PIPEX_DIR = ../pipex
PIPEX_LIB = $(PIPEX_DIR)/pipex.a

# 📂 Directorios de código y objetos
SRCDIR = src
OBJDIR = obj

# 🔍 Buscar archivos fuente en subdirectorios
SRCS := $(shell find $(SRCDIR) -type f -name "*.c")
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# 🎨 Colores
RED      = \033[0;31m
GREEN    = \033[0;32m
YELLOW   = \033[0;33m
MAGENTA  = \033[0;35m
CYAN     = \033[0;36m
WHITE    = \033[0;37m
RESET    = \033[0m

# 🚀 Compilación principal
all: libs $(NAME)

# 🔗 Compilar librerías en orden correcto
libs:
	@echo "$(CYAN)📦 Compilando librerías...$(RESET)"
	@make --no-print-directory -C $(LIBFT_DIR)
	@echo "$(CYAN)------------------------------------------------------------$(RESET)"
	@make --no-print-directory -C $(HISTORY_DIR)
	@echo "$(CYAN)------------------------------------------------------------$(RESET)"
	@make --no-print-directory -C $(ENVIROMENT_DIR)
	@echo "$(CYAN)------------------------------------------------------------$(RESET)"
	@make --no-print-directory -C $(BUILTINS_DIR)
	@echo "$(CYAN)------------------------------------------------------------$(RESET)"
	@make --no-print-directory -C $(PROMPT_DIR)
	@echo "$(CYAN)------------------------------------------------------------$(RESET)"
	@make --no-print-directory -C $(TOKENS_DIR)
	@echo "$(CYAN)------------------------------------------------------------$(RESET)"
	@make --no-print-directory -C $(PIPEX_DIR)
	@echo "$(CYAN)------------------------------------------------------------$(RESET)"
	@echo "$(GREEN)✅ Librerías compiladas.$(RESET)"

# 🔨 Compilar programa principal
$(NAME): $(OBJDIR) $(OBJS) $(LIBFT_LIB) $(HISTORY_LIB) $(ENVIROMENT_LIB) $(BUILTINS_LIB) $(PROMPT_LIB) $(TOKENS_LIB) $(PIPEX_LIB)
	@echo "$(CYAN)🔗 Enlazando $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -lreadline -lhistory $(PIPEX_LIB) $(TOKENS_LIB) $(PROMPT_LIB) $(BUILTINS_LIB) $(ENVIROMENT_LIB) $(HISTORY_LIB) $(LIBFT_LIB) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) compilada con éxito.$(RESET)"

# 📂 Crear directorios de objetos
$(OBJDIR):
	@echo "$(GREEN)📂 Creando directorios de objetos...$(RESET)"
	@mkdir -p $(OBJDIR)
	@find $(SRCDIR) -type d | sed 's|$(SRCDIR)|$(OBJDIR)|' | xargs -I {} mkdir -p {}
	@echo "$(GREEN)✅ Directorios de objetos creados.$(RESET)"

# 🏗 Compilar archivos .c en .o, respetando subdirectorios
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@) > /dev/null 2>&1  # 🔹 Crear subdirectorios si no existen
	@echo "$(YELLOW)🔹 Compilando $< -> $@$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ > /dev/null 2>&1
	@echo "$(GREEN)✅ Compilado: $@$(RESET)"

# 🧹 Limpieza
clean:
	@echo "$(RED)🗑️ Eliminando archivos objeto...$(RESET)"
	@$(RM) $(OBJS) > /dev/null 2>&1
	@echo "$(MAGENTA)✅ Limpieza de objetos completada.$(RESET)"

# 🧹 Limpieza total
fclean: clean
	@echo "$(RED)🚮 Eliminando ejecutable $(NAME)...$(RESET)"
	@$(RM) $(NAME) > /dev/null 2>&1
	@echo "$(MAGENTA)✅ $(NAME) eliminado.$(RESET)"
	@echo "$(RED)🧹 Limpiando librerías...$(RESET)"
	@make --no-print-directory -C $(LIBFT_DIR) fclean > /dev/null 2>&1
	@make --no-print-directory -C $(HISTORY_DIR) fclean > /dev/null 2>&1
	@make --no-print-directory -C $(ENVIROMENT_DIR) fclean > /dev/null 2>&1
	@make --no-print-directory -C $(BUILTINS_DIR) fclean > /dev/null 2>&1
	@make --no-print-directory -C $(PROMPT_DIR) fclean > /dev/null 2>&1
	@make --no-print-directory -C $(TOKENS_DIR) fclean > /dev/null 2>&1
	@make --no-print-directory -C $(PIPEX_DIR) fclean > /dev/null 2>&1
	@echo "$(MAGENTA)✅ Librerías limpiadas.$(RESET)"

# 🔄 Recompilación completa
re: fclean all

.PHONY: all clean fclean re libs