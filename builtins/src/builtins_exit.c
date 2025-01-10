#include "../builtinsft.h"

// Función para manejar el comando exit
int ft_exit(char **args)
{
    int status = 0;

    if (args[1] != NULL)  // Si se proporciona un argumento, usarlo como código de salida
    {
        status = ft_atoi(args[1]);
    }

    exit(status);
}