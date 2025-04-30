/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:30:02 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/30 15:35:12 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

void	ft_free_command(t_command *cmd)
{
	int	j;

	if (!cmd)
		return ;
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
}

void	ft_free_executor(t_executor *exec)
{
	int	i;

	if (!exec)
		return ;
	i = 0;
	while (i < exec->count)
	{
		ft_free_command(exec->commands[i]);
		i++;
	}
	free(exec->commands);
	free(exec);
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
