/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:55:34 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/13 03:21:23 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../enviromentft.h"

void	ft_free_env(t_Env *env_list)
{
	t_Env	*tmp;

	while (env_list)
	{
		tmp = env_list->next;
		free(env_list->key);
		free(env_list->value);
		free(env_list);
		env_list = tmp;
	}
}
