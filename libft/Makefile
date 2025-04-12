NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Iinclude

AR = ar rcs
RM = rm -f

# 📂 Directorios de librerías externas
SRC_DIR = ./src
OBJ_DIR = ./obj

# 📜 Buscar automáticamente todos los archivos fuente en src/ y sus subdirectorios
SRCS = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

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

# 🔗 Crear librería .a (libft.a)
$(NAME): $(OBJ_DIR) $(OBJS)
	@echo "$(CYAN)🔗 Creando $(NAME)...$(RESET)"
	@$(AR) $(NAME) $(OBJS)
	@echo "$(GREEN)✅ $(NAME) creado con éxito.$(RESET)"

# 📂 Crear directorio de objetos
$(OBJ_DIR):
	@echo "$(CYAN)📂 Creando directorios de objetos...$(RESET)"
	@mkdir -p $(OBJ_DIR)
	@echo "$(GREEN)✅ Directorios de objetos creados.$(RESET)"

# 🏗 Compilar archivos `.c` en `.o`, respetando subdirectorios
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	@echo "$(YELLOW)🔹 Compilando $< -> $@$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)✅ Compilado: $@$(RESET)"

# 🧹 Limpiar archivos objeto
clean:
	@echo "$(RED)🗑️  Eliminando archivos objeto...$(RESET)"
	@$(RM) $(OBJS)
	@echo "$(MAGENTA)✅ Limpieza de objetos completada.$(RESET)"

# 🧹 Limpiar completamente (incluye la librería)
fclean: clean
	@if [ -d "$(OBJDIR)" ]; then \
		echo "$(RED)🚮 Eliminando directorio de objetos...$(RESET)"; \
		$(RM) -rf $(OBJDIR); \
		echo "$(MAGENTA)✅ Directorio obj eliminado.$(RESET)"; \
	fi
	@if [ -f "$(NAME)" ]; then \
		echo "$(RED)🚮 Eliminando archivo $(NAME)...$(RESET)"; \
		$(RM) $(NAME); \
		echo "$(MAGENTA)✅ $(NAME) eliminado.$(RESET)"; \
	fi

# 🔄 Recompilación completa
re: fclean all

.PHONY: all clean fclean re
