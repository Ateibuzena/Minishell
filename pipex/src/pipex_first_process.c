/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_first_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 20:27:44 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/21 21:29:15 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

/*
void print_open_fds()
{
    fprintf(stderr, "\n--- FD abiertos antes de outfile ---\n");
    for (int fd = 0; fd < 10; fd++)
    {
        if (fcntl(fd, F_GETFD) != -1)
            fprintf(stderr, "FD %d está en uso\n", fd);
    }
    fprintf(stderr, "\n");
}

static void ft_first_fork(t_pipex *pipex, char **env)
{
	fprintf(stderr, "\nEntro en first fork con pipex->argv[pipex->cmd]: %s\n", pipex->argv[pipex->cmd]);
    // Redirigir la entrada
    if (pipex->infile != STDIN_FILENO)
    {
        dup2(pipex->infile, STDIN_FILENO);
        close(pipex->infile);
    }

    // Redirigir la salida
    if (pipex->outfile != STDOUT_FILENO)
    {
        dup2(pipex->outfile, STDOUT_FILENO);
        close(pipex->outfile);
    }
    else // Si no hay outfile, escribir en la pipe
    {
        close(pipex->pipes[pipex->count][READ]);
        dup2(pipex->pipes[pipex->count][WRITE], STDOUT_FILENO);
        close(pipex->pipes[pipex->count][WRITE]);
    }

    fprintf(stderr, "Hijo del primer proceso\n");
    print_open_fds();
    ft_execute(pipex, env);
    exit(1);
}

static void ft_close_fds_parent(t_pipex *pipex)
{
    if (pipex->infile != STDIN_FILENO)
        close(pipex->infile);
    if (pipex->outfile != STDOUT_FILENO)
        close(pipex->outfile);
    close(pipex->pipes[pipex->count][WRITE]); // Cerrar escritura después del fork
    fprintf(stderr, "Padre del primer proceso\n");
    print_open_fds();
    fprintf(stderr, "**************************************************\n");
}

void ft_first_process(t_pipex *pipex, char **env)
{
    ft_create_pipe(pipex);
    char **split = NULL;

    // Manejo de lectura y redirecciones antes de ejecutar
    while (pipex->i < pipex->size && !ft_strchr(pipex->argv[pipex->i], '|'))
    {
        split = ft_split(pipex->argv[pipex->i], ' ');
        ft_handle_lecture(pipex, split);
        ft_handle_redirection(pipex, split);
        ft_is_command(pipex, split[0]);
        ft_freedouble(split);
        pipex->i++;
    }
    pipex->pids[pipex->count] = fork();
    if (pipex->pids[pipex->count] == -1)
        return (ft_perror("Fork error: first process\n"));
    else if (pipex->pids[pipex->count] == 0)
    {
        ft_first_fork(pipex, env);
        fprintf(stderr, "**************************************************\n");
    }
    else
    {
        ft_close_fds_parent(pipex);
        pipex->status = ft_waitpid(pipex->pids[pipex->count]);
    }
    pipex->i++;
    pipex->count++;
}
*/