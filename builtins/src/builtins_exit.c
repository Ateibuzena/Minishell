/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:05:19 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/02 23:06:16 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtinsft.h"

int	ft_exit(char **args)
{
	int		status;
	char	*arg;
	int		i;

	i = 0;
	status = 0;
	if (args[1] != NULL)
	{
		arg = args[1];
		while (arg[i] != '\0')
		{
			if (!ft_isdigit(arg[i]) && (arg[i] != '-' || i == 0))
			{
				ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
				ft_putstr_fd(arg, STDERR_FILENO);
				ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
				return (1);
			}
			i++;
		}
		status = ft_atoi(args[1]);
	}
	//ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (status != 0)
		g_exit = status;
	else if (status == 0)
		g_exit = -1;
	return (status);
}
