#include "../builtinsft.h"

// Función para manejar el comando env
int ft_env(t_env *env, char **args)
{
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
    t_env *current = env;
    while (current)
    {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }

    return (1);
}