/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_session.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:22:09 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/01 13:15:19 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../promptft.h"

char	*ft_find_session(char *value)
{
	char	*start;

	start = ft_strstr(value, "local/");
	if (start)
		return (start);
	return (ft_strstr(value, "unix/"));
}

char	*ft_extract_session(t_Env *env)
{
	char	*start;
	char	*end;
	char	*session_id;

	while (env && (ft_strcmp(env->key, "SESSION_MANAGER") == 0))
		env = env->next;
	if (!env)
		return (NULL);
	start = ft_find_session(env->value);
	if (start)
	{
		start += 6;
		end = ft_strstr(start, ".42malaga.com");
		if (end && end > start)
		{
			session_id = malloc((end - start + 1) * sizeof(char));
			if (session_id)
			{
				ft_strncpy(session_id, start, end - start);
				session_id[end - start] = '\0';
				return (session_id);
			}
		}
	}
	return (NULL);
}
