/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:15:39 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/21 21:29:40 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"
/*
// Contar comandos
static void	ft_count_cmds(t_pipex *pipex, char *input[])
{
	int	i;

	i = 0;
	pipex->n = 0;
	while (input[i])
	{
		if (ft_strcmp(input[i], "|") != 0)
			pipex->n++;
		i++;
	}
	if (pipex->n)
		pipex->n += 1;
}

// Asigna memoria para pipex->argv
static int	ft_copy_argv(t_pipex *pipex, char *input[])
{
	int	i;

	i = 0;
	pipex->argv = malloc(sizeof(char *) * (ft_strlen_double(input) + 1));
	if (!pipex->argv)
		return (ft_perror("Malloc error: argv\n"), 0);
	while (input[i])
	{
		pipex->argv[i] = ft_strdup(input[i]);
		if (!pipex->argv[i])
			return (ft_perror("Malloc error: argv[i]\n"), 0);
		i++;
	}
	pipex->argv[i] = NULL;
	pipex->size = i;
	return (1);
}

// Asigna memoria para pipex->pids
static int	ft_alloc_pids(t_pipex *pipex)
{
	pipex->pids = malloc(pipex->n * sizeof(pid_t));
	if (!pipex->pids)
		return (ft_perror("Malloc error: pids\n"), 0);
	return (1);
}

// Inicializar estructura pipex
void	ft_init(t_pipex *pipex, char *input[], t_History *history)
{
	pipex->status = 0;
	pipex->cmd = -1;
	pipex->history = history;
	pipex->i = 0;
	pipex->count = 0;
	pipex->infile = STDIN_FILENO;
	pipex->outfile = STDOUT_FILENO;
	ft_count_cmds(pipex, input);
	if (!ft_copy_argv(pipex, input) || !ft_alloc_pids(pipex))
		return (ft_free_pipex(&pipex), exit(EXIT_FAILURE));
}
*/