NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I.

AR = ar rcs
RM = rm -f

# 📂 Directorios de código y objetos
SRCDIR = src
OBJDIR = obj

# 🔍 Buscar archivos fuente en subdirectorios
SRCS := $(shell find $(SRCDIR) -type f -name "*.c")
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

HEADERS = libft.h

# 🎨 Colores
RED      = \033[0;31m
GREEN    = \033[0;32m
YELLOW   = \033[0;33m
MAGENTA  = \033[0;35m
CYAN     = \033[0;36m
WHITE    = \033[0;37m
RESET    = \033[0m

# 🚀 Compilación principal
all: $(NAME)

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

# 🔄 Recompilación completa
re: fclean all

.PHONY: all clean fclean re
