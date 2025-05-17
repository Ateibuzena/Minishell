/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:05:19 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/17 19:28:20 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtinsft.h"

int	ft_exit(char **args)
{
	if (args[1] != NULL)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": not argument required\n", STDERR_FILENO);
		g_exit = 1;
		return (1);
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	g_exit = 1;
	return (0);
}
