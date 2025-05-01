/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:55:27 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/01 23:56:16 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishellft.h"

int	ft_handle_redirection_type(char *arg, int *i)
{
	if (ft_strncmp(arg, "<", 1) == 0)
	{
		if (ft_strncmp(arg, "<<", 2) == 0)
		{
			if (ft_redirect_input(arg + 2, arg + 2) < 0)
				return (-1);
			(*i)++;
		}
		else
		{
			if (ft_redirect_input(arg + 1, NULL) < 0)
				return (-1);
		}
	}
	else if (ft_strncmp(arg, ">", 1) == 0)
	{
		if (ft_redirect_output(arg + 1) < 0)
			return (-1);
	}
	else if (ft_strncmp(arg, ">>", 2) == 0)
	{
		if (ft_redirect_append(arg + 2) < 0)
			return (-1);
	}
	return (0);
}

int	ft_handle_redirections(char **argv, int *stdin, int *stdout)
{
	int	i;

	i = 0;
	if (!argv || !argv[0])
		return (-1);
	ft_save_descriptors(stdin, stdout);
	while (argv[i])
	{
		if (ft_handle_redirection_type(argv[i], &i) < 0)
			return (-1);
		i++;
	}
	return (0);
}
