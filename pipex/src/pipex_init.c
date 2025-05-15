/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:05:37 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/14 21:48:34 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

t_command	*ft_init_command(int len)
{
	t_command	*command;

	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	command->cmd = ft_calloc(len + 1, sizeof(char *));
	if (!command->cmd)
	{
		free(command);
		return (NULL);
	}
	command->infile = NULL;
	command->outfile = NULL;
	command->heredoc = NULL;
	command->append = 0;
	return (command);
}

static int	ft_init_commands(t_executor **exec, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		(*exec)->commands[i] = ft_init_command(len);
		if (!(*exec)->commands[i])
		{
			while (--i >= 0)
				ft_free_command((*exec)->commands[i], len);
			free((*exec)->commands);
			(*exec)->commands = NULL;
			free(*exec);
			exec = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

t_executor	*ft_init_executor(int len)
{
	t_executor	*exec;

	exec = ft_calloc(1, sizeof(t_executor));
	if (!exec)
		return (NULL);
	exec->commands = ft_calloc(len + 1, sizeof(t_command *));
	if (!exec->commands)
	{
		free(exec);
		return (NULL);
	}
	if (!ft_init_commands(&exec, len))
		return (NULL);

	exec->count = 0;
	return (exec);
}
