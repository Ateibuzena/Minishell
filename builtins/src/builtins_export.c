/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:03:37 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/31 16:16:38 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtinsft.h"

static int	ft_valid_key(const char *key)
{
	int	i;

	i = 0;
	if (key == NULL || !ft_isalpha(key[0]))
		return (0);
	while (key[i] != '\0')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_parse_key_value(char *arg, char **key, char **value)
{
	*key = ft_strtok(arg, "=");
	*value = ft_strtok(NULL, "");
	if (!(*key && *value))
	{
		ft_putstr_fd("minishell: export: invalid argument\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

static int	ft_process_export(t_Env **env, char *key)
{
	char	*expanded_key;
	char	**keys_to_unset;

	expanded_key = ft_expand_variables(key, *env);
	if (!ft_valid_key(expanded_key))
	{
		ft_putstr_fd("minishell: export: invalid key\n", STDERR_FILENO);
		free(expanded_key);
		return (0);
	}
	keys_to_unset = malloc(sizeof(char *) * 3);
	if (!keys_to_unset)
	{
		ft_putstr_fd("minishell: export: memory allocation error\n",
			STDERR_FILENO);
		free(expanded_key);
		return (0);
	}
	keys_to_unset[0] = NULL;
	keys_to_unset[1] = ft_strdup(expanded_key);
	keys_to_unset[2] = NULL;
	ft_unset(env, keys_to_unset);
	free(keys_to_unset[1]);
	free(keys_to_unset);
	return (1);
}

static void	ft_store_env_variable(t_Env **env, char *key, char *value)
{
	char	*expanded_value;
	char	*expanded_key;

	expanded_key = ft_expand_variables(key, *env);
	expanded_value = ft_expand_variables(value, *env);
	ft_add_env(env, expanded_key, expanded_value);
	free(expanded_key);
	free(expanded_value);
}

int	ft_export(t_Env **env, char **args)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	while (args[i] != NULL)
	{
		if (!ft_parse_key_value(args[i], &key, &value))
			return (0);
		if (!ft_process_export(env, key))
			return (0);
		ft_store_env_variable(env, key, value);
		i++;
	}
	return (1);
}
