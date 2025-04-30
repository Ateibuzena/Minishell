/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:05:37 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/30 13:09:52 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

t_command	*ft_init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_command));
	cmd->cmd = malloc(sizeof(char *) * 256);
	if (!cmd->cmd)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
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
