/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_last_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 20:44:17 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/16 21:32:31 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

// Función para redirecciones
static void ft_redirections(t_pipex *pipex)
{
	char **split;

	split = NULL;
	while (pipex->i < pipex->size)
    {
        split = ft_split(pipex->argv[pipex->i], ' ');
        ft_handle_lecture(pipex, split);
		ft_handle_redirection(pipex, split);
        if ((ft_strcmp(split[0], "<") == 0) && (ft_strcmp(split[0], "<<") == 0)
                    && (ft_strcmp(split[0], ">") == 0) && (ft_strcmp(split[0], ">>") == 0))
                pipex->cmd = pipex->i;
        ft_freedouble(split);
        pipex->i++;
    }
}

// Función para el hijo
static void ft_middle_forks(t_pipex *pipex, char **env)
{
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
		dup2(pipex->outfile, STDOUT_FILENO);
		close(pipex->outfile);
	}
	ft_execute(pipex, env);
	exit(1);

}

// Función para cerrar los fds innecesarios
static void ft_close_fds(t_pipex *pipex)
{
	//close(pipex->pipes[pipex->count - 1][READ]);
	if (pipex->infile != STDIN_FILENO)
        close(pipex->infile);
    else
        close(pipex->pipes[pipex->count - 1][READ]);
    if (pipex->outfile != STDOUT_FILENO)
		close(pipex->outfile);
}

// Función para el último proceso
void ft_last_process(t_pipex *pipex, char **env)
{
	if (pipex->count >= pipex->n)
        return ;
	ft_redirections(pipex);
    pipex->pids[pipex->count] = fork();
    if (pipex->pids[pipex->count] == -1)
        return (ft_perror("Fork error: Last process"));
    else if (pipex->pids[pipex->count] == 0)
		ft_middle_forks(pipex, env);
	else
	{
		ft_close_fds(pipex);
		pipex->status = ft_waitpid(pipex->pids[pipex->count]);
	}
	pipex->i += 1;
	pipex->count += 1;
}
