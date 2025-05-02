NAME = parser.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I. -I../pipex -I../libft 

AR = ar rcs
RM = rm -f

# 📂 Librerías externas
LIBFT_DIR = ../libft	
LIBFT_LIB = $(LIBFT_DIR)/libft.a

PIPEX_DIR = ../pipex
PIPEX_LIB = $(PIPEX_DIR)/pipex.a

# 📂 Directorios de código y objetos
SRCDIR = src
OBJDIR = obj

# 🔍 Buscar archivos fuente en subdirectorios
SRCS := $(shell find $(SRCDIR) -type f -name "*.c")
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

HEADERS = parserft.h

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
	@make --no-print-directory -C $(PIPEX_DIR)
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
	@if [ -f "$(LIBFT_LIB)" ]; then \
		echo "$(RED)🚮 Eliminando librería externa $(LIBFT_LIB)...$(RESET)"; \
		make -C $(LIBFT_DIR) fclean; \
		echo "$(MAGENTA)✅ Librería $(LIBFT_LIB) eliminada.$(RESET)"; \
	fi

# 🔄 Recompilación completa
re: fclean all

.PHONY: all clean fclean re libs