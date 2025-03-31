/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:34:24 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/31 16:35:32 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtinsft.h"

static char	*ft_get_env(t_Env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) != 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*ft_expand_variables(const char *arg, t_Env *env)
{
	char	*value;
	char	*result;

	if (arg[0] == '$')
	{
		value = ft_get_env(env, arg + 1);
		if (value)
		{
			result = ft_strdup(value);
			return (result);
		}
	}
	return (ft_strdup(arg));
}
