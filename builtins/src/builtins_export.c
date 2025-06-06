/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:03:37 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/24 17:27:33 by azubieta         ###   ########.fr       */
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

static int	ft_parse_key_value(char *arg, char **key, char **value, char **dup)
{
	*dup = ft_strdup(arg);
	if (!*dup)
	{
		ft_putstr_fd("minishell: export: dup error\n", STDERR_FILENO);
		return (0);
	}
	*key = ft_strtok(*dup, "=");
	*value = ft_strtok(NULL, "");
	if (!(*key))
	{
		ft_putstr_fd("minishell: export: invalid argument\n", STDERR_FILENO);
		return (0);
	}
	if (!*value)
		*value = "";
	return (1);
}

static int	ft_process_export(t_Env **env, char *key)
{
	char	**keys_to_unset;

	if (!ft_valid_key(key))
	{
		ft_putstr_fd("minishell: export: invalid key\n", STDERR_FILENO);
		return (0);
	}
	keys_to_unset = malloc(sizeof(char *) * 3);
	if (!keys_to_unset)
	{
		ft_putstr_fd("minishell: export: memory allocation error\n",
			STDERR_FILENO);
		return (0);
	}
	keys_to_unset[0] = NULL;
	keys_to_unset[1] = ft_strdup(key);
	keys_to_unset[2] = NULL;
	ft_unset(env, keys_to_unset);
	free(keys_to_unset[1]);
	free(keys_to_unset);
	return (1);
}

int	ft_export(t_Env **env, char **args)
{
	int		i;
	char	*key;
	char	*value;
	char	*dup;

	i = 1;
	dup = NULL;
	while (args[i] != NULL)
	{
		if (!ft_parse_key_value(args[i], &key, &value, &dup))
			return (free(dup), 1);
		if (!ft_process_export(env, key))
			return (free(dup), 1);
		ft_add_env(env, key, value);
		free(dup);
		i++;
	}
	return (0);
}
