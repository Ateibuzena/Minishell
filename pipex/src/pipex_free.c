/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:37:57 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/21 21:29:26 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"
/*
// Actualizamos la función ft_free_pipes
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
	free(pipes);  // Libera el array de punteros
}

// Actualización de ft_free_pipex
void	ft_free_pipex(t_pipex **pipex)
{
	if (!pipex || !(*pipex))
		return ;

	// Verificamos y mostramos las direcciones antes de liberar
	if ((*pipex)->argv)
	{
		//printf("Freeing argv at address: %p\n", (void *)(*pipex)->argv);
		ft_freedouble((*pipex)->argv);
		(*pipex)->argv = NULL;  // Establecemos el puntero a NULL
	}
	if ((*pipex)->clean_paths)
	{
		//printf("Freeing clean_paths at address: %p\n", (void *)(*pipex)->clean_paths);
		ft_freedouble((*pipex)->clean_paths);
		(*pipex)->clean_paths = NULL;  // Establecemos el puntero a NULL
	}
	if ((*pipex)->commands)
	{
		//printf("Freeing commands at address: %p\n", (void *)(*pipex)->commands);
		ft_freedouble((*pipex)->commands);
		(*pipex)->commands = NULL;  // Establecemos el puntero a NULL
	}
	if ((*pipex)->found_way)
	{
		//printf("Freeing found_way at address: %p\n", (void *)(*pipex)->found_way);
		free((*pipex)->found_way);
		(*pipex)->found_way = NULL;  // Establecemos el puntero a NULL
	}
	if ((*pipex)->pipes)
	{
		//printf("Freeing pipes at address: %p\n", (void *)(*pipex)->pipes);
		ft_free_pipes((*pipex)->pipes, (*pipex)->n);
		(*pipex)->pipes = NULL;  // Establecemos el puntero a NULL
	}
	if ((*pipex)->pids)
	{
		//printf("Freeing pids at address: %p\n", (void *)(*pipex)->pids);
		free((*pipex)->pids);
		(*pipex)->pids = NULL;  // Establecemos el puntero a NULL
	}

	// Liberamos la estructura principal
	//printf("Freeing pipex structure at address: %p\n", (void *)*pipex);
	if (pipex)
	{
		free(*pipex);
		*pipex = NULL;  // Establecemos el puntero a NULL
	}
}
*/