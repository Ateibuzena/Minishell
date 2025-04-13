/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:01:07 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/13 17:49:29 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtinsft.h"

int	ft_env(t_Env *env, char **args)
{
	t_Env	*current;

	if (args[1] != NULL)
	{
		printf("minishell: env: no arguments allowed\n");
		return (1);
	}
	if (env == NULL)
	{
		printf("minishell: env: no environment variables found\n");
		return (1);
	}
	current = env;
	while (current)
	{
		if (current->key && current->value)
			printf("%s=%s\n", current->key, current->value);
		else
			printf("minishell: env: invalid environment variable\n");
		current = current->next;
	}
	return (0);
}
