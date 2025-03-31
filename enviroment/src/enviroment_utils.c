/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:46:27 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/31 20:12:21 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../enviromentft.h"

void	ft_split_env(const char *env_entry, char **key, char **value)
{
	char	*equal_sign;

	if (!env_entry || !key || !value)
		return ;
	equal_sign = ft_strchr(env_entry, '=');
	if (equal_sign)
	{
		*key = ft_strndup(env_entry, equal_sign - env_entry);
		*value = ft_strdup(equal_sign + 1);
	}
	else
    {
        *key = ft_strdup(env_entry);
        *value = NULL;
    }
}

t_Env	*ft_create_node(const char *key, const char *value)
{
	t_Env	*node;

	if (!key)
		return (NULL);
	node = (t_Env *)malloc(sizeof(t_Env));
	if (!node)
	{
		perror("malloc failed");
		exit(1);
	}
	node->key = ft_strdup(key);
	node->value = value ? ft_strdup(value) : NULL;
	node->next = NULL;
	return (node);
}

void	ft_add_node(t_Env **env_list, t_Env *new_node)
{
	t_Env	*current;

	if (!new_node)
		return ;
	if (!*env_list)
	{
		*env_list = new_node;
		return ;
	}
	current = *env_list;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	ft_delete_env(t_Env **head, const char *key)
{
	t_Env	*temp;
	t_Env	*prev;

	prev = NULL;
	temp = *head;
	if (temp != NULL && ft_strcmp(temp->key, key) != 0)
	{
		*head = temp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
		return ;
	}
	while (temp != NULL && ft_strcmp(temp->key, key) == 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	free(temp->key);
	free(temp->value);
	free(temp);
}

void	ft_add_env(t_Env **env, const char *key, const char *value)
{
	t_Env	*new_node;
	t_Env	*current;

	new_node = (t_Env *)malloc(sizeof(t_Env));
	current = *env;
	if (!new_node)
	{
		perror("Error al agregar variable de entorno");
		exit(1);
	}
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (*env == NULL)
		*env = new_node;
	else
	{
		while (current->next)
		{
			current = current->next;
		}
		current->next = new_node;
	}
}
