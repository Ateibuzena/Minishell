/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:03:37 by azubieta          #+#    #+#             */
/*   Updated: 2025/01/10 17:54:08 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtinsft.h"
// Función para agregar una variable de entorno a la lista
void ft_add_env(t_env **env, const char *key, const char *value)
{
    t_env *new_node = (t_env *)malloc(sizeof(t_env));
    t_env *current = *env;

    if (!new_node)
	{
        perror("Error al agregar variable de entorno");
        exit(1);
    }

    new_node->key = ft_strdup(key);
    new_node->value = ft_strdup(value);
    new_node->next = NULL;

    if (*env == NULL)
	{
        *env = new_node;
    } 
	else
	{
        while (current->next)
		{
            current = current->next;
        }
        current->next = new_node;
    }
}

// Función para manejar el comando export
int ft_export(t_env **env, char **args)
{
    if (args[1] != NULL)  // Si hay un argumento, agregar o modificar la variable
    {
        char *key = ft_strtok(args[1], "=");
        char *value = ft_strtok(NULL, "");

        if (key && value)
        {
            ft_add_env(env, key, value);  // Agregar la nueva variable al entorno
        }
        else
        {
            fprintf(stderr, "minishell: export: invalid argument\n");
            return 1;
        }
    }

    t_env *current = *env;
    while (current)
	{
        printf("export %s=%s\n", current->key, current->value);
        current = current->next;
    }

    return (1);
}
