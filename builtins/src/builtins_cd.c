/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:30:53 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/22 21:18:08 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtinsft.h"

int	ft_cd(char **args)
{
	int	error;

	error = -1;
	if (args[1] == NULL
		|| (args[1][0] == '-' && args[1][1] == '-' && args[1][2] == '\0'))
	{
		error = ft_change_home();
		//fprintf(stderr, "error en cd if: %d\n", error);
	}
	else if (args[1][0] == '-' && args[1][1] == '\0')
	{
		error = ft_change_oldpwd(args);
		//fprintf(stderr, "error en cd else if: %d\n", error);
	}
	else
	{
		error = ft_expand_directory(args[1]);
		//fprintf(stderr, "error en cd else: %d\n", error);
	}
	return (error);
}
