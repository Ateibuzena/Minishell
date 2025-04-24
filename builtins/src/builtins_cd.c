/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:30:53 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/24 18:06:21 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtinsft.h"

int	ft_cd(char **args)
{
	int	error;

	error = -1;
	if (args[1] == NULL
		|| (args[1][0] == '-' && args[1][1] == '-' && args[1][2] == '\0'))
		error = ft_change_home();
	else if (args[1][0] == '-' && args[1][1] == '\0')
		error = ft_change_oldpwd(args);
	else
		error = ft_expand_directory(args[1]);
	return (error);
}
