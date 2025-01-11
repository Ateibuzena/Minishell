/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:03:37 by azubieta          #+#    #+#             */
/*   Updated: 2025/01/11 16:12:04 by azubieta         ###   ########.fr       */
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
int ft_export(t_env **env, char **args)
{
    char *key;
    char *value;
    //t_env *current;

    if (args[1] != NULL)  // Si hay un argumento, agregar o modificar la variable
    {
        key = ft_strtok(args[1], "=");
        value = ft_strtok(NULL, "");

        if (key && value)
        {
            // Validar la clave antes de agregarla
            if (!ft_valid_key(key))
            {
                ft_putstr_fd("minishell: export: invalid key\n", STDERR_FILENO);
                return (1);
            }
            else
                ft_add_env(env, key, value);  // Agregar la nueva variable al entorno
        }
        else
        {
            ft_putstr_fd("minishell: export: invalid argument\n", STDERR_FILENO);
            return (1);
        }
    }

    /*current = *env;
    while (current)
	{
        printf("export %s=%s\n", current->key, current->value);
        current = current->next;
    }*/

    return (1);
}
