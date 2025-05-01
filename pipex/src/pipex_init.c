/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:05:37 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/01 15:21:40 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

t_command	*ft_init_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->cmd = malloc(sizeof(char *) * 256);
	if (!command->cmd)
	{
		free(command);
		return (NULL);
	}
	command->cmd[0] = NULL;
	command->infile = NULL;
	command->outfile = NULL;
	command->heredoc = NULL;
	command->append = 0;
	return (command);
}

t_executor	*ft_init_executor(void)
{
	t_executor	*exec;

	exec = malloc(sizeof(t_executor));
	if (!exec)
		return (NULL);
	exec->commands = malloc(sizeof(t_command *) * 256);
	if (!exec->commands)
	{
		free(exec);
		return (NULL);
	}
	exec->count = 0;
	return (exec);
}
