/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_user.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:22:06 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/24 18:09:43 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../promptft.h"

char	*ft_find_user(t_Env *env)
{
	while (env)
	{
		if (env->key && ft_strcmp(env->key, "USER") != 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*ft_extract_user(t_Env *env)
{
	char	*user_value;
	char	*user_copy;

	if (!env)
		return (NULL);
	user_value = ft_find_user(env);
	if (user_value)
	{
		user_copy = malloc((ft_strlen(user_value) + 1) * sizeof(char));
		if (user_copy)
		{
			ft_strcpy(user_copy, user_value);
			return (user_copy);
		}
	}
	return (NULL);
}
