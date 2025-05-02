NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I. -I../parser -I../pipex -I../tokens -I../prompt -I../builtins -I../enviroment -I../history -I../signals -I../libft

RM = rm -f

# 📂 Librerías externas
LIBFT_DIR = ../libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

SIGNALS_DIR = ../signals
SIGNALS_LIB = $(SIGNALS_DIR)/signals.a

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

PARSER_DIR = ../parser
PARSER_LIB = $(PARSER_DIR)/parser.a

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
	@make --no-print-directory -C $(SIGNALS_DIR)
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
	@make --no-print-directory -C $(PARSER_DIR)
	@echo "$(CYAN)------------------------------------------------------------$(RESET)"
	@echo "$(GREEN)✅ Librerías compiladas.$(RESET)"

# 🔨 Compilar programa principal
$(NAME): $(OBJDIR) $(OBJS) $(LIBFT_LIB) $(SIGNALS_LIB) $(HISTORY_LIB) $(ENVIROMENT_LIB) $(BUILTINS_LIB) $(PROMPT_LIB) $(TOKENS_LIB) $(PIPEX_LIB) $(PARSER_LIB)
	@echo "$(CYAN)🔗 Enlazando $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -lreadline -lhistory $(PARSER_LIB) $(PIPEX_LIB) $(TOKENS_LIB) $(PROMPT_LIB) $(BUILTINS_LIB) $(ENVIROMENT_LIB) $(HISTORY_LIB) $(SIGNALS_LIB) $(LIBFT_LIB) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) compilada con éxito.$(RESET)"

# 📂 Crear directorios de objetos
$(OBJDIR):
	@echo "$(GREEN)📂 Creando directorios de objetos...$(RESET)"
	@mkdir -p $(OBJDIR)
	@find $(SRCDIR) -type d | sed 's|$(SRCDIR)|$(OBJDIR)|' | xargs -I {} mkdir -p {}
	@echo "$(GREEN)✅ Directorios de objetos creados.$(RESET)"

# 🏗 Compilar archivos `.c` en `.o`, respetando subdirectorios
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)🔹 Compilando $< -> $@$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)✅ Compilado: $@$(RESET)"

# 🧹 Limpieza
clean:
	@echo "$(RED)🗑️  Eliminando archivos objeto...$(RESET)"
	@$(RM) $(OBJS)
	@echo "$(MAGENTA)✅ Limpieza de objetos completada.$(RESET)"
	@if [ -d "$(OBJDIR)" ]; then \
		echo "$(RED)🚮 Eliminando directorio de objetos...$(RESET)"; \
		$(RM) -rf $(OBJDIR); \
		echo "$(MAGENTA)✅ Directorio obj eliminado.$(RESET)"; \
	fi

# 🧹 Limpieza total (elimina objetos y archivo .a)
fclean: clean
	@if [ -f "$(NAME)" ]; then \
		echo "$(RED)🚮 Eliminando archivo $(NAME)...$(RESET)"; \
		$(RM) $(NAME); \
		echo "$(MAGENTA)✅ $(NAME) eliminado.$(RESET)"; \
	fi
	@if [ -f "$(PARSER_LIB)" ]; then \
		echo "$(RED)🚮 Eliminando librería externa $(PARSER_LIB)...$(RESET)"; \
		make -C $(PARSER_DIR) fclean; \
		echo "$(MAGENTA)✅ Librería $(PARSER_LIB) eliminada.$(RESET)"; \
	fi
	@if [ -f "$(PIPEX_LIB)" ]; then \
		echo "$(RED)🚮 Eliminando librería externa $(PIPEX_LIB)...$(RESET)"; \
		make -C $(PIPEX_DIR) fclean; \
		echo "$(MAGENTA)✅ Librería $(PIPEX_LIB) eliminada.$(RESET)"; \
	fi
	@if [ -f "$(TOKENS_LIB)" ]; then \
		echo "$(RED)🚮 Eliminando librería externa $(TOKENS_LIB)...$(RESET)"; \
		make -C $(TOKENS_DIR) fclean; \
		echo "$(MAGENTA)✅ Librería $(TOKENS_LIB) eliminada.$(RESET)"; \
	fi
	@if [ -f "$(PROMPT_LIB)" ]; then \
		echo "$(RED)🚮 Eliminando librería externa $(PROMPT_LIB)...$(RESET)"; \
		make -C $(PROMPT_DIR) fclean; \
		echo "$(MAGENTA)✅ Librería $(PROMPT_LIB) eliminada.$(RESET)"; \
	fi
	@if [ -f "$(BUILTINS_LIB)" ]; then \
		echo "$(RED)🚮 Eliminando librería externa $(BUILTINS_LIB)...$(RESET)"; \
		make -C $(BUILTINS_DIR) fclean; \
		echo "$(MAGENTA)✅ Librería $(BUILTINS_LIB) eliminada.$(RESET)"; \
	fi
	@if [ -f "$(ENVIROMENT_LIB)" ]; then \
		echo "$(RED)🚮 Eliminando librería externa $(ENVIROMENT_LIB)...$(RESET)"; \
		make -C $(ENVIROMENT_DIR) fclean; \
		echo "$(MAGENTA)✅ Librería $(ENVIROMENT_LIB) eliminada.$(RESET)"; \
	fi
	@if [ -f "$(HISTORY_LIB)" ]; then \
		echo "$(RED)🚮 Eliminando librería externa $(HISTORY_LIB)...$(RESET)"; \
		make -C $(HISTORY_DIR) fclean; \
		echo "$(MAGENTA)✅ Librería $(HISTORY_LIB) eliminada.$(RESET)"; \
	fi
	@if [ -f "$(SIGNALS_LIB)" ]; then \
		echo "$(RED)🚮 Eliminando librería externa $(SIGNALS_LIB)...$(RESET)"; \
		make -C $(SIGNALS_DIR) fclean; \
		echo "$(MAGENTA)✅ Librería $(SIGNALS_LIB) eliminada.$(RESET)"; \
	fi
	@if [ -f "$(LIBFT_LIB)" ]; then \
		echo "$(RED)🚮 Eliminando librería externa $(LIBFT_LIB)...$(RESET)"; \
		make -C $(LIBFT_DIR) fclean; \
		echo "$(MAGENTA)✅ Librería $(LIBFT_LIB) eliminada.$(RESET)"; \
	fi

# 🔄 Recompilación completa
re: fclean all

.PHONY: all clean fclean re