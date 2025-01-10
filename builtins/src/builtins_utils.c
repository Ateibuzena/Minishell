/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:46:27 by azubieta          #+#    #+#             */
/*   Updated: 2025/01/10 19:35:42 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtinsft.h"

void ft_split_env(const char *env_entry, char **key, char **value)
{
    char *equal_sign = ft_strchr(env_entry, '=');
    if (equal_sign)
    {
        *key = ft_strndup(env_entry, equal_sign - env_entry); // Copiar hasta el '='
        *value = ft_strdup(equal_sign + 1);                  // Copiar después del '='
    }
    else
    {
        *key = ft_strdup(env_entry); // Si no hay '=', todo es key
        *value = NULL;
    }
}

t_env *ft_create_node(const char *key, const char *value)
{
    t_env *node = (t_env *)malloc(sizeof(t_env));
    if (!node)
    {
        perror("malloc failed");
        exit(1);
    }
    node->key = ft_strdup(key);
    node->value = value ? ft_strdup(value) : NULL;
    node->next = NULL;
    return node;
}


void ft_add_node(t_env **env_list, t_env *new_node)
{
    if (!*env_list)
    {
        *env_list = new_node;
        return;
    }
    t_env *current = *env_list;
    while (current->next)
        current = current->next;
    current->next = new_node;
}

t_env *ft_copy_env(char **envp)
{
    t_env *env_list;
    t_env *new_node;
    char *key;
    char *value;
    int  i;

    i = 0;
    env_list = NULL;
    while (envp[i])
    {
        ft_split_env(envp[i], &key, &value);  // Separar key y value
        new_node = ft_create_node(key, value); // Crear nodo
        ft_add_node(&env_list, new_node);  // Agregar nodo a la lista
        free(key);
        free(value);
        i++;
    }
    return (env_list);
}

void ft_free_env(t_env *env_list)
{
    t_env *tmp;
    while (env_list)
    {
        tmp = env_list;
        env_list = env_list->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
}