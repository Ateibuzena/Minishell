#include "../builtinsft.h"

static int ft_valid_key(const char *key)
{
    int i;

    if (!key || *key == '\0')  // La clave no puede ser vacía
        return (0);

    // La clave debe comenzar con una letra o un guión bajo
    if (!ft_isalpha(*key) && *key != '_')
        return (0);
    i = 1;
    // Verificar que el resto de los caracteres sean alfanuméricos o guión bajo
    while (key[i] != '\0')
    {
        if (!ft_isalnum(key[i]) && key[i] != '_')
            return (0);
        i++;
    }

    return (1);
}

// Función para manejar el comando unset

int ft_unset(t_Env **env, char **args)
{
    int i;
    
    i = 1;
    if (args[1] == NULL)
    {
        fprintf(stderr, "minishell: unset: expected argument\n");
        return (1);
    }

    // Recorrer y eliminar las variables de entorno
    while (args[i] != NULL)
    {
        // Verificar si la clave es válida
        if (!ft_valid_key(args[i]))
        {
            fprintf(stderr, "minishell: unset: invalid key: %s\n", args[i]);
            continue ;  // Continuar con el siguiente argumento
        }
        else
            ft_delete_env(env, args[i]);  // Eliminar la variable de entorno
        i++;
    }

    return (1);
}