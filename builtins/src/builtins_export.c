/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:03:37 by azubieta          #+#    #+#             */
/*   Updated: 2025/02/22 21:25:14 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtinsft.h"

// Función para verificar que la clave es válida
static int ft_valid_key(const char *key)
{
    int i;

    i = 0;
    if (key == NULL || !ft_isalpha(key[0])) // La clave no debe empezar con un número
        return (0);

    while (key[i] != '\0')
    {
        if (!ft_isalnum(key[i]) && key[i] != '_')  // Solo caracteres alfanuméricos o '_'
            return (0);
        i++;
    }
    return (1);
}

// Función para manejar el comando export
// Función para manejar el comando export
int ft_export(t_Env **env, char **args)
{
    char *key;
    char *value;
    char *expanded_value;
    char *expanded_key;
    // Añadir las nuevas variables
    int i = 1;

    char **keys_to_unset = NULL;

    while (args[i] != NULL)
    {
        key = ft_strtok(args[i], "=");
        value = ft_strtok(NULL, "");

        if (key && value)
        {
            expanded_key = ft_expand_variables(key, *env);
            fprintf(stderr, "expanded_key: %s\n", expanded_key);
            if (!ft_valid_key(expanded_key))
            {
                ft_putstr_fd("minishell: export: invalid key\n", STDERR_FILENO);
                free(expanded_key);
                return (0);
            }

            // Crear lista con solo la key y NULL
            keys_to_unset = malloc(sizeof(char *) * 3); // Un elemento + NULL
            if (!keys_to_unset)
            {
                ft_putstr_fd("minishell: export: memory allocation error\n", STDERR_FILENO);
                free(expanded_key);
                return (0);
            }
            keys_to_unset[0] = NULL;
            keys_to_unset[1] = ft_strdup(expanded_key);
            keys_to_unset[2] = NULL;

            // Llamar a unset con la lista
            ft_unset(env, keys_to_unset);

            // Expandir el valor y añadir al entorno
            expanded_value = ft_expand_variables(value, *env);
            ft_add_env(env, expanded_key, expanded_value);

            // Liberar memoria
            free(keys_to_unset[0]);
            free(keys_to_unset);
            free(expanded_key);
            free(expanded_value);
        }
        else
        {
            ft_putstr_fd("minishell: export: invalid argument\n", STDERR_FILENO);
            return (0);
        }

        i++;
    }
    return (1);
}
