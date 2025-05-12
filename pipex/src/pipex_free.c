/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:30:02 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/12 23:20:35 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

void	ft_free_command(t_command *cmd)
{
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
	if (cmd->cmd)
		ft_freedouble(cmd->cmd);
}

void	ft_free_executor(t_executor *exec)
{
	int	i;

	if (!exec)
		return ;
	if (exec->commands)
	{
		i = 0;
		while (i < exec->count)
		{
			if (exec->commands[i])
			{
				ft_free_command(exec->commands[i]);
				exec->commands[i] = NULL;
			}
			i++;
		}
		free(exec->commands);
		exec->commands = NULL;
	}
	free(exec);
	exec = NULL;
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	free(s1);
	return (result);
}
