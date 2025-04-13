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
SRCS := $(shell find $(SRCDIR) -type f -name "*.c")

# 🔍 Buscar archivos fuente en subdirectorios
OBJDIR = obj
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
all: $(LIBFT_DIR) $(HISTORY_DIR) $(ENVIROMENT_DIR) $(BUILTINS_DIR) $(PROMPT_DIR) $(TOKENS_DIR) $(PIPEX_DIR) $(NAME)

# 🔗 Compilar librerías en orden correcto
$(LIBFT_LIB):
	@echo "$(CYAN)📦 Compilando librería libft...$(RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)✅ Librería libft compilada.$(RESET)"

$(HISTORY_LIB): $(LIBFT_LIB)
	@echo "$(CYAN)📦 Compilando librería history...$(RESET)"
	@make -C $(HISTORY_DIR)
	@echo "$(GREEN)✅ Librería history compilada.$(RESET)"

$(ENVIROMENT_LIB): $(LIBFT_LIB)
	@echo "$(CYAN)📦 Compilando librería enviroment...$(RESET)"
	@make -C $(ENVIROMENT_DIR)
	@echo "$(GREEN)✅ Librería enviroment compilada.$(RESET)"

$(BUILTINS_LIB): $(LIBFT_LIB)
	@echo "$(CYAN)📦 Compilando librería builtins...$(RESET)"
	@make -C $(BUILTINS_DIR)
	@echo "$(GREEN)✅ Librería builtins compilada.$(RESET)"

$(PROMPT_LIB): $(LIBFT_LIB)
	@echo "$(CYAN)📦 Compilando librería prompt...$(RESET)"
	@make -C $(PROMPT_DIR)
	@echo "$(GREEN)✅ Librería prompt compilada.$(RESET)"

$(TOKENS_LIB): $(LIBFT_LIB)	
	@echo "$(CYAN)📦 Compilando librería tokens...$(RESET)"
	@make -C $(TOKENS_DIR)
	@echo "$(GREEN)✅ Librería tokens compilada.$(RESET)"

$(PIPEX_LIB): $(LIBFT_LIB)
	@echo "$(CYAN)📦 Compilando librería pipex...$(RESET)"
	@make -C $(PIPEX_DIR)
	@echo "$(GREEN)✅ Librería pipex compilada.$(RESET)"

# 🔨 Compilar programa principal
$(NAME): $(OBJDIR) $(OBJS) $(LIBFT_LIB) $(HISTORY_LIB) $(ENVIROMENT_LIB) $(BUILTINS_LIB) $(PROMPT_LIB) $(TOKENS_LIB) $(PIPEX_LIB)
	@echo "$(CYAN)🔗 Enlazando $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(PIPEX_LIB) $(TOKENS_LIB) $(PROMPT_LIB) $(BUILTINS_LIB) $(ENVIROMENT_LIB) $(HISTORY_LIB) $(LIBFT_LIB) -lreadline -lhistory -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) compilada con éxito.$(RESET)"

# 📂 Crear directorio de objetos
$(OBJDIR):
	@echo "$(CYAN)📂 Creando directorios de objetos...$(RESET)"
	@mkdir -p $(OBJDIR)
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
	@if [ -f "$(LIBFT_LIB)" ]; then \
		echo "$(RED)🚮 Eliminando librería externa $(LIBFT_LIB)...$(RESET)"; \
		make -C $(LIBFT_DIR) fclean; \
		echo "$(MAGENTA)✅ Librería $(LIBFT_LIB) eliminada.$(RESET)"; \
	fi

# 🔄 Recompilación completa
re: fclean all

.PHONY: all clean fclean re