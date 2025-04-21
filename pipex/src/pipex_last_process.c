/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_last_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 20:44:17 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/21 21:30:36 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"
/*
static void ft_last_fork(t_pipex *pipex, char **env)
{
	fprintf(stderr, "\nEntro en last fork con pipex->argv[pipex->cmd]: %s\n", pipex->argv[pipex->cmd]);
    close(pipex->pipes[pipex->count - 1][WRITE]); // Cerrar escritura en la pipe anterior
    
    // Asegurar que la entrada es de la tubería anterior
    dup2(pipex->pipes[pipex->count - 1][READ], STDIN_FILENO);
    close(pipex->pipes[pipex->count - 1][READ]); // Ya no necesitamos leer de la pipe

    // Si hay salida redirigida a archivo, usarlo
    if (pipex->outfile != STDOUT_FILENO)
    {
        dup2(pipex->outfile, STDOUT_FILENO);
        close(pipex->outfile);
    }
    
    fprintf(stderr, "last proceso ejecutando: %s\n", pipex->argv[pipex->cmd]);
	print_open_fds();
    ft_execute(pipex, env);
    //fprintf(stderr, "+++++++++++++++++++++++++++++++++++++++++++++++++\n");
    exit(1);
}

static void ft_close_fds(t_pipex *pipex)
{
    close(pipex->pipes[pipex->count - 1][WRITE]);
    close(pipex->pipes[pipex->count - 1][READ]);
    if (pipex->outfile != STDOUT_FILENO)
		close(pipex->outfile);
	fprintf(stderr, "Padre de último proceso\n");
	print_open_fds();
	fprintf(stderr, "+++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

void ft_last_process(t_pipex *pipex, char **env)
{
	if (pipex->count >= pipex->n)
		return ;
	
    pipex->pids[pipex->count] = fork();
    if (pipex->pids[pipex->count] == -1)
        return (ft_perror("Fork error: last process\n"));
    else if (pipex->pids[pipex->count] == 0)
    {
		ft_last_fork(pipex, env);
		fprintf(stderr, "+++++++++++++++++++++++++++++++++++++++++++++++++\n");
	}
    else
    {
        ft_close_fds(pipex);
        pipex->status = ft_waitpid(pipex->pids[pipex->count]);
    }
}
*/