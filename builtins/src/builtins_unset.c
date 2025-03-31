/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:31:11 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/31 16:34:06 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtinsft.h"

static int	ft_valid_key(const char *key)
{
	int	i;

	if (!key || *key == '\0')
		return (0);
	if (!ft_isalpha(*key) && *key != '_')
		return (0);
	i = 1;
	while (key[i] != '\0')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_unset(t_Env **env, char **args)
{
	int	i;

	i = 1;
	if (args[1] == NULL)
	{
		printf("minishell: unset: expected argument\n");
		return (1);
	}
	while (args[i] != NULL)
	{
		if (!ft_valid_key(args[i]))
		{
			printf("minishell: unset: invalid key: %s\n", args[i]);
			continue ;
		}
		else
			ft_delete_env(env, args[i]);
		i++;
	}
	return (1);
}
