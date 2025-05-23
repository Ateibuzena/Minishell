/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:30:02 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/23 11:52:19 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

void	ft_free_command(t_command *cmd, int len)
{
	if (!cmd)
		return ;
	if (cmd->infile)
	{
		free(cmd->infile);
		cmd->infile = NULL;
	}
	if (cmd->outfile)
	{
		free(cmd->outfile);
		cmd->outfile = NULL;
	}
	if (cmd->heredoc)
	{
		free(cmd->heredoc);
		cmd->heredoc = NULL;
	}
	if (cmd->cmd)
		ft_free_partialdouble(cmd->cmd, len);
	free(cmd);
	cmd = NULL;
}

void	ft_free_executor(t_executor *exec)
{
	int	i;

	if (!exec)
		return ;
	if (exec->commands)
	{
		i = 0;
		while (i < exec->len)
		{
			if (exec->commands[i])
				ft_free_command(exec->commands[i], exec->len_commands);
			i++;
		}
		free(exec->commands);
		exec->commands = NULL;
	}
	free(exec);
	exec = NULL;
}

void	ft_free_pipex(t_pipex *pipex)
{
	if (!pipex)
		return ;
	ft_free_executor(pipex->exec);
	ft_freedouble(pipex->env_array);
	ft_free_history(pipex->history);
	ft_free_env((*pipex->env));
}
