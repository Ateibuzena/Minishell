/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:37:57 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/31 20:20:49 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

static void	ft_free_pipes(int **pipes, int n)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < n)
	{
		if (pipes[i])
			free(pipes[i]);
		i++;
	}
	free(pipes);
	pipes = NULL;
}

void	ft_free_pipex(t_pipex **pipex)
{
	if (!pipex || !(*pipex))
		return ;
	if ((*pipex)->argv)
		ft_freedouble((*pipex)->argv);
	if ((*pipex)->clean_paths)
		ft_freedouble((*pipex)->clean_paths);
	if ((*pipex)->commands)
		ft_freedouble((*pipex)->commands);
	if ((*pipex)->found_way)
		free((*pipex)->found_way);
	ft_free_pipes((*pipex)->pipes, (*pipex)->n);
	if ((*pipex)->pids)
		free((*pipex)->pids);
	(*pipex)->argv = NULL;
	(*pipex)->clean_paths = NULL;
	(*pipex)->commands = NULL;
	(*pipex)->found_way = NULL;
	(*pipex)->pids = NULL;
	(*pipex)->pipes = NULL;
	(*pipex)->n = 0;
	free(*pipex);
	*pipex = NULL;
}
