/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_first_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 20:27:44 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/31 22:10:07 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static void print_open_fds()
{
    fprintf(stderr, "\n--- FD abiertos antes de outfile ---\n");
    for (int fd = 0; fd < 10; fd++)
    {
        if (fcntl(fd, F_GETFD) != -1)
            fprintf(stderr, "FD %d está en uso\n", fd);
    }
    fprintf(stderr, "\n");
}


static void	ft_first_fork(t_pipex *pipex, char **env)
{
	close(pipex->pipes[pipex->count][READ]);
	if (pipex->infile != STDIN_FILENO)
	{
		dup2(pipex->infile, STDIN_FILENO);
		close(pipex->infile);
	}
	if (pipex->outfile == STDOUT_FILENO && (pipex->n != 0))
	{
		dup2(pipex->pipes[pipex->count][WRITE], STDOUT_FILENO);
		close(pipex->pipes[pipex->count][WRITE]);
	}
	else if (pipex->outfile != STDOUT_FILENO)
	{
		printf("\nFIRST PROCESS outfile FD justo antes de dup2: %d\n", pipex->outfile);
		printf("\nFIRST PROCESS Probando fcntl: %d\n", fcntl(pipex->outfile, F_GETFD));
		dup2(pipex->outfile, STDOUT_FILENO);
		close(pipex->outfile);
	}
	fprintf(stderr, "hijo de first process\n");
	print_open_fds();
	ft_execute(pipex, env);
	exit(1);
}

static void	ft_close_fds(t_pipex *pipex)
{
	close(pipex->pipes[pipex->count][READ]);
	if (pipex->infile != STDIN_FILENO)
		close(pipex->infile);
	if (pipex->outfile == STDOUT_FILENO && (pipex->n != 0))
		close(pipex->pipes[pipex->count][WRITE]);
	else if (pipex->outfile != STDOUT_FILENO)
		close(pipex->outfile);
	fprintf(stderr, "padre de first process\n");
	print_open_fds();
}

void	ft_first_process(t_pipex *pipex, char **env)
{
	char	**split;

	split = NULL;
	ft_create_pipe(pipex);
	while (pipex->i < pipex->size && !ft_strchr(pipex->argv[pipex->i], '|'))
	{
		split = ft_split(pipex->argv[pipex->i], ' ');
		ft_handle_lecture(pipex, split);
		printf("\nFIRST PROCESS pipex->argv[pipex->i]: %s\n", pipex->argv[pipex->i]);
		//print_open_fds();
		ft_handle_redirection(pipex, split);
		printf("\nFIRST PROCESS outfile FD antes de dup2 despues de handle_redirection: %d\n", pipex->outfile);
		ft_is_command(pipex, split[0]);
		ft_freedouble(split);
		pipex->i++;
	}
	pipex->pids[pipex->count] = fork();
	if (pipex->pids[pipex->count] == -1)
		return (ft_perror("Fork error: first process\n"));
	else if (pipex->pids[pipex->count] == 0)
		ft_first_fork(pipex, env);
	else
	{
		ft_close_fds(pipex);
		pipex->status = ft_waitpid(pipex->pids[pipex->count]);
	}
	pipex->i += 1;
	pipex->count += 1;
}
