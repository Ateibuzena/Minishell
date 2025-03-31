/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_first_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 20:27:44 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/31 19:25:50 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

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
		dup2(pipex->outfile, STDOUT_FILENO);
		close(pipex->outfile);
	}
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
		ft_handle_redirection(pipex, split);
		if ((ft_strcmp(split[0], "<") == 0) && (ft_strcmp(split[0], "<<") == 0)
			&& (ft_strcmp(split[0], ">") == 0) && (ft_strcmp(split[0], ">>") == 0))
			pipex->cmd = pipex->i;
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
