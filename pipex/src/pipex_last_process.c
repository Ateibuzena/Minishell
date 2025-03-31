/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_last_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 20:44:17 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/31 22:16:33 by azubieta         ###   ########.fr       */
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
static void	ft_redirections(t_pipex *pipex)
{
	char	**split;

	split = NULL;
	while (pipex->i < pipex->size)
	{
		split = ft_split(pipex->argv[pipex->i], ' ');
		ft_handle_lecture(pipex, split);
		printf("\nLAST PROCESS pipex->argv[pipex->i]: %s\n", pipex->argv[pipex->i]);
		//print_open_fds();
		ft_handle_redirection(pipex, split);
		printf("\nLAST PROCESS outfile FD antes de dup2 despues de handle_redirection en last process: %d\n", pipex->outfile);
		ft_is_command(pipex, split[0]);
		ft_freedouble(split);
		pipex->i++;
	}
}

static void	ft_last_fork(t_pipex *pipex, char **env)
{
	printf("\nfd justo antes de las redirecciones: %d\n", pipex->outfile);
	close(pipex->pipes[pipex->count][READ]);
	if (pipex->infile != STDIN_FILENO)
	{
		dup2(pipex->infile, STDIN_FILENO);
		close(pipex->infile);
	}
	else
	{
		dup2(pipex->pipes[pipex->count - 1][READ], STDIN_FILENO);
		close(pipex->pipes[pipex->count - 1][READ]);
	}
	if (pipex->outfile != STDOUT_FILENO)
	{
		printf("\nLAST PROCESS outfile FD justo antes de dup2: %d\n", pipex->outfile);
		printf("\nLAST PROCESS Probando fcntl: %d\n", fcntl(pipex->outfile, F_GETFD));
		if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
			ft_perror("Dup2 error: Last process");
		close(pipex->outfile);
	}
	fprintf(stderr, "hijo de last process\n");
	print_open_fds();
	ft_execute(pipex, env);
	exit(1);
}

static void	ft_close_fds(t_pipex *pipex)
{
	close(pipex->pipes[pipex->count][READ]);
	if (pipex->infile != STDIN_FILENO)
		close(pipex->infile);
	else
		close(pipex->pipes[pipex->count - 1][READ]);
	if (pipex->outfile != STDOUT_FILENO)
		close(pipex->outfile);
	fprintf(stderr, "padre de last process\n");
	print_open_fds();
}

void	ft_last_process(t_pipex *pipex, char **env)
{
	if (pipex->count >= pipex->n)
		return ;
	ft_create_pipe(pipex);
	ft_redirections(pipex);
	printf("redirection antes del fork: %d\n", pipex->outfile);
	printf("lecture: %d\n", pipex->infile);
	printf("pipex->cmd: %d %s\n", pipex->cmd, pipex->argv[pipex->cmd]);
	pipex->pids[pipex->count] = fork();
	if (pipex->pids[pipex->count] == -1)
		return (ft_perror("Fork error: Last process"));
	else if (pipex->pids[pipex->count] == 0)
		ft_last_fork(pipex, env);
	else
	{
		ft_close_fds(pipex);
		pipex->status = ft_waitpid(pipex->pids[pipex->count]);
	}
	pipex->i += 1;
	pipex->count += 1;
}
