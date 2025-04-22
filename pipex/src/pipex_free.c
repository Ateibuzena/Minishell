/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:30:02 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/22 20:30:09 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

void	free_partial_executor(t_executor *exec)
{
	int	i, j;

	if (!exec)
		return;
	for (i = 0; i < exec->count; i++)
	{
		t_command *cmd = exec->commands[i];
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		if (cmd->cmd)
		{
			for (j = 0; cmd->cmd[j]; j++)
				free(cmd->cmd[j]);
			free(cmd->cmd);
		}
		free(cmd);
	}
	free(exec->commands);
	free(exec);
}

void	free_executor(t_executor *exec)
{
	int	i, j;

	if (!exec)
		return;
	i = 0;
	while (i < exec->count)
	{
		t_command *cmd = exec->commands[i];

		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		if (cmd->cmd)
		{
			j = 0;
			while (cmd->cmd[j])
			{
				free(cmd->cmd[j]);
				j++;
			}
			free(cmd->cmd);
		}
		free(cmd);
		i++;
	}
	free(exec->commands);
	free(exec);
}