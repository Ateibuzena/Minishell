NAME = builtins.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I. -I../enviroment -I../history -I../signals -I../libft 

AR = ar rcs
RM = rm -f

# 📂 Librerías externas
ENVIROMENT_DIR = ../enviroment
ENVIROMENT_LIB = $(ENVIROMENT_DIR)/enviroment.a

HISTORY_DIR = ../history
HISTORY_LIB = $(HISTORY_DIR)/history.a

SIGNALS_DIR = ../signals
SIGNALS_LIB = $(SIGNALS_DIR)/signals.a

LIBFT_DIR = ../libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# 📂 Directorios de código y objetos
SRCDIR = src
OBJDIR = obj

# 🔍 Buscar archivos fuente en subdirectorios
SRCS := $(shell find $(SRCDIR) -type f -name "*.c")
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

HEADERS = builtinsft.h

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
	@echo "$(GREEN)✅ Librerías compiladas.$(RESET)"

# 🔨 Crear archivo .a (builtins.a)
$(NAME): $(OBJDIR) $(OBJS)
	@echo "$(CYAN)🔗 Creando $(NAME)...$(RESET)"
	@$(AR) $(NAME) $(OBJS)
	@echo "$(GREEN)✅ $(NAME) creado con éxito.$(RESET)"

# 📂 Crear directorio de objetos
$(OBJDIR):
	@echo "$(CYAN)📂 Creando directorios de objetos...$(RESET)"
	@mkdir -p $(OBJDIR)
	@echo "$(GREEN)✅ Directorios de objetos creados.$(RESET)"

# 🏗 Compilar archivos `.c` en `.o`, respetando subdirectorios
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR)
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)🔹 Compilando $< -> $@$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)✅ Compilado: $@$(RESET)"

# 🧹 Limpieza de objetos
clean:
	@echo "$(RED)🗑️  Eliminando archivos objeto...$(RESET)"
	@$(RM) $(OBJS)
	@echo "$(MAGENTA)✅ Limpieza de objetos completada.$(RESET)"
	@if [ -f "$(OBJDIR)" ]; then \
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

.PHONY: all clean fclean re libs
