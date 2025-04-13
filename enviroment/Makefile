NAME = enviroment.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I. -I../libft

AR = ar rcs
RM = rm -f

# 📂 Librerías externas
LIBFT_DIR = ../libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# 📂 Directorios de código y objetos
SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*.c)

OBJDIR = obj
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

HEADERS = enviromentft.h

# 🎨 Colores
RED      = \033[0;31m
GREEN    = \033[0;32m
YELLOW   = \033[0;33m
MAGENTA  = \033[0;35m
CYAN     = \033[0;36m
WHITE    = \033[0;37m
RESET    = \033[0m

# 🚀 Compilación principal
all: $(LIBFT_LIB) $(NAME)

# 🔗 Compilar librerías en orden correcto
$(LIBFT_LIB):
	@echo "$(CYAN)📦 Compilando librería libft...$(RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)✅ Librería libft compilada.$(RESET)"

# 🔨 Crear archivo .a (enviroment.a)
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
	@if [ -d "$(LIBFT_DIR)" ]; then \
		echo "$(RED)🚮 Eliminando librería externa $(LIBFT_LIB)...$(RESET)"; \
		make -C $(LIBFT_DIR) fclean; \
		echo "$(MAGENTA)✅ Librería externa $(LIBFT_LIB) eliminada.$(RESET)"; \
	fi

# 🔄 Recompilación completa
re: fclean all

.PHONY: all clean fclean re
