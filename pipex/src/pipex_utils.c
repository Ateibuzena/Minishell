/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:43:13 by azubieta          #+#    #+#             */
/*   Updated: 2025/02/21 19:49:52 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

void	ft_close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->pipes)
	{
		while (i < pipex->n - 1)
		{
			close(pipex->pipes[i][READ]);
			close(pipex->pipes[i][WRITE]);
			i++;
		}
	}
}

void	ft_free_pipex(t_pipex **pipex)
{
	int	i;

	if (!(*pipex))
		return ;
	i = 0;
	if ((*pipex)->argv)
	{
		while ((*pipex)->argv[i])
		{
			free((*pipex)->argv[i]);
			i++;
		}
		free((*pipex)->argv);
	}
	i = 0;
	if ((*pipex)->pipes)
	{
		while (i < (*pipex)->n - 1 && (*pipex)->pipes[i])
		{
			close((*pipex)->pipes[i][READ]);
			close((*pipex)->pipes[i][WRITE]);
			free((*pipex)->pipes[i]);
			i++;
		}
		free((*pipex)->pipes);
	}
	if ((*pipex)->clean_paths)
		ft_freedouble((*pipex)->clean_paths);
	if ((*pipex)->commands)
		ft_freedouble((*pipex)->commands);
	if ((*pipex)->pids)
		free((*pipex)->pids);
	free((*pipex));
}

void	ft_waitpid(t_pipex *pipex)
{
	int	i;
	int	status;

	i = 0;
	while (i < (pipex->n))
	{
		if (waitpid(-1, &status, 0) == pipex->pids[pipex->n - 1])
			pipex->status = WEXITSTATUS(status);
		i++;
	}
}