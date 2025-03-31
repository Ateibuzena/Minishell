/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:53:20 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/31 17:30:31 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../enviromentft.h"

t_Env	*ft_copy_env(char **envp)
{
	t_Env	*env_list;
	t_Env	*new_node;
	char	*key;
	char	*value;
	int		i;

	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		ft_split_env(envp[i], &key, &value);
		new_node = ft_create_node(key, value);
		ft_add_node(&env_list, new_node);
		free(key);
		free(value);
		i++;
	}
	return (env_list);
}
