#include "../builtinsft.h"

// Función para manejar el comando env
int ft_env(t_env *env, char **args)
{
    t_env *current;

    // Si se pasa un argumento adicional, mostrar un error
    if (args[1] != NULL)
    {
        fprintf(stderr, "minishell: env: no arguments allowed\n");
        return (1);
    }

    // Si la lista de variables de entorno está vacía, también mostrar un mensaje de error
    if (env == NULL)
    {
        fprintf(stderr, "minishell: env: no environment variables found\n");
        return (1);
    }

    // Recorremos la lista de variables de entorno e imprimimos en el formato "KEY=value"
    current = env;
    while (current)
    {
        if (current->key && current->value)  // Comprobamos que key y value no sean NULL
        {
            printf("%s=%s\n", current->key, current->value);
        }
        else
        {
            fprintf(stderr, "minishell: env: invalid environment variable (key or value is NULL)\n");
        }
        current = current->next;
    }

    return (1);
}
