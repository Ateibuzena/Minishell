#include "../builtinsft.h"

// Función para manejar el comando exit
int ft_exit(char **args)
{
    int     status;
    char    *arg;
    int     i;

    i = 0;
    status = 0;
    // Si se proporciona más de un argumento, mostrar un error
    if (args[1] != NULL)
    {
        // Comprobamos que el argumento sea un número válido
        arg = args[1];
        while (arg[i] != '\0')
        {
            if (!ft_isdigit(arg[i]) && (arg[i] != '-' || i == 0))  // Permite el signo '-' solo al principio
            {
                ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
                ft_putstr_fd(arg, STDERR_FILENO);
                ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
                return (1);  // Retornamos 1 indicando error
            }
            i++;
        }
        status = ft_atoi(args[1]);  // Si el argumento es válido, convertimos a número
    }
    //ft_putstr_fd("exit", STDOUT_FILENO);
    // Salimos con el código de salida determinado
    exit(status);
}
