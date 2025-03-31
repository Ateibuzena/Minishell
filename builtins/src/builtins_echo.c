/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:34:41 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/31 20:41:19 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtinsft.h"

// Función para verificar si el argumento es un "-n" válido
static int	ft_n_flag(const char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

// Función para manejar el comando echo
int	ft_echo(char **args, t_Env *env)
{
	int		i;
	int		newline;
	char	*expanded;

	newline = 1;
	i = 1;
	while (args[i] && ft_n_flag(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		expanded = ft_expand_variables(args[i], env);
		printf("%s", expanded);
		free(expanded);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (1);
}
