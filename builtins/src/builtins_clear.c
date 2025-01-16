#include "../builtinsft.h"

void ft_clear(void)
{
    // Esto imprime el código ANSI para limpiar la terminal
    write(STDOUT_FILENO, "\033[H\033[J", 7);
}