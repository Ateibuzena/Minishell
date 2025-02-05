/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:37:22 by azubieta          #+#    #+#             */
/*   Updated: 2025/02/02 18:24:01 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

void	ft_child_process(int input_fd, int output_fd)
{
	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
			(close(output_fd), close(input_fd), exit(1));
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
			(close(output_fd), exit(1));
		close(output_fd);
	}
}

void	ft_first_process(t_pipex *pipex, char **env)
{
	fprintf(stderr, "entro en first_process\n");
	int	infile;

	pipex->i = 1;
	pipex->pids[0] = fork();
	pipex->count += 1;
	if (pipex->pids[0] < 0)
		(ft_free_pipex(&pipex), exit(1));
	if (pipex->pids[0] == 0)
	{
		if (pipex->here_doc == 1)
			infile = ft_here_doc(pipex->argv[0]);	
		else if (pipex->redirection == 1)
		{
			//fprintf(stderr, "entro\n");
			infile = open(pipex->argv[0], O_RDONLY);

		}
		else
		{
			//fprintf(stderr, "entro 2\n");
			infile = STDIN_FILENO;

		}
		if (infile < 0)
			(ft_errno(pipex->argv[0]), ft_free_pipex(&pipex), exit(1));
		else
		{
			close(pipex->pipes[0][READ]);
			ft_child_process(infile, pipex->pipes[0][WRITE]);
			ft_execute_cmd(pipex, pipex->argv[pipex->i], env, NULL);
			fprintf(stderr, "salgo de first_process\n");
		}
	}
	fprintf(stderr, "padre salgo de first_process\n");
	close(pipex->pipes[0][WRITE]);
}

int	ft_middle_process(t_pipex *pipex, char **env)
{
	int	i;
	int	j;

	fprintf(stderr, "entro en middle process\n");
	j = -1;
	if (pipex->here_doc)
		j = 0;
	i = 1;
	while (i < (pipex->n - 1))
	{
		pipex->pids[i] = fork();
		pipex->count += 1;
		if (pipex->pids[i] < 0)
			(ft_free_pipex(&pipex), exit(1));
		if (pipex->pids[i] == 0)
		{
			close(pipex->pipes[i][READ]);
			ft_child_process(pipex->pipes[i - 1][READ], pipex->pipes[i][WRITE]);
			ft_execute_cmd(pipex, pipex->argv[i + j + 2], env, NULL);
			fprintf(stderr, "salgo de middle_process\n");
		}
		close(pipex->pipes[i - 1][READ]);
		close(pipex->pipes[i][WRITE]);
		i++;
	}
	fprintf(stderr, "padre salgo de middle_prcess\n");
	return (i);
}

void	ft_last_process(t_pipex *pipex, char **env)
{
	fprintf(stderr, "entro en last_process\n");
	int	outfile;

	pipex->pids[pipex->i] = fork();
	pipex->count += 1;
	if (pipex->pids[pipex->i] < 0)
		(ft_free_pipex(&pipex), exit(1));
	if (pipex->pids[pipex->i] == 0)
	{
		if (pipex->here_doc == 1)
		{
			//fprintf(stderr, "entro 1\n");
			outfile = open(pipex->argv[pipex->n + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);	
		}
		else if (pipex->redirection == 1)
		{
			//fprintf(stderr, "entro 2\n");
			outfile = open(pipex->argv[pipex->n + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else
		{
			//fprintf(stderr, "entro 3\n");
			outfile = STDOUT_FILENO;

		}
		if (outfile < 0)
			(ft_errno(pipex->argv[pipex->n + 1]), ft_free_pipex(&pipex), exit(1));
		ft_child_process(pipex->pipes[pipex->i - 1][READ], outfile);
		ft_execute_cmd(pipex, pipex->argv[pipex->n], env, NULL);
		fprintf(stderr, "salgo de last_process\n");
	}
	fprintf(stderr, "padre salgo de last_process\n");
	close(pipex->pipes[pipex->i - 1][READ]);
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

/*void    ft_waitpid(t_pipex *pipex)
{
    int     i;
    int     status;

    i = 0;
    while (i < pipex->n)
	{
        // Espera a cada proceso hijo individualmente
        if (waitpid(pipex->pids[i], &status, 0) == pipex->pids[i])
		{
            // Si el proceso terminó correctamente, guarda el estado de salida
            if (WIFEXITED(status))
                pipex->status = WEXITSTATUS(status);
            // Si el proceso terminó por una señal, guarda el código de la señal
            else if (WIFSIGNALED(status))
                pipex->status = 128 + WTERMSIG(status);
        }
        i++;
    }
}*/

