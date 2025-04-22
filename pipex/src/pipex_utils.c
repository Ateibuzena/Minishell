/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:43:13 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/22 05:18:49 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"
/*
void	ft_close_pipes(t_pipex *pipex)
{
	int	i;

	if (!pipex || !pipex->pipes)
		return ;
	i = 0;
	while (i < pipex->n - 1)
	{
		if (pipex->pipes[i])
		{
			if (close(pipex->pipes[i][READ]) == -1)
				ft_perror("Error closing pipe (READ)\n");
			if (close(pipex->pipes[i][WRITE]) == -1)
				ft_perror("Error closing pipe (WRITE)\n");
		}
		i++;
	}
}


void	ft_is_command(t_pipex *pipex, char *str)
{
	if ((ft_strcmp(str, "<") == 0) && (ft_strcmp(str, "<<") == 0)
		&& (ft_strcmp(str, ">") == 0) && (ft_strcmp(str, ">>") == 0))
		pipex->cmd = pipex->i;
}

void	ft_create_pipe(t_pipex *pipex)
{
	int	**new_pipes;

	new_pipes = realloc(pipex->pipes, sizeof(int *) * (pipex->count + 1));
	if (!new_pipes)
	{
		ft_perror("Error al redimensionar pipes\n");
		ft_free_pipex(&pipex);
		exit(1);
	}
	pipex->pipes = new_pipes;
	pipex->pipes[pipex->count] = malloc(sizeof(int) * 2);
	if (!pipex->pipes[pipex->count])
	{
		ft_perror("Error al asignar memoria a pipes[count]\n");
		ft_free_pipex(&pipex);
		exit(1);
	}
	if (pipe(pipex->pipes[pipex->count]) < 0)
	{
		free(pipex->pipes[pipex->count]);
		ft_perror("Error al crear pipe\n");
		ft_free_pipex(&pipex);
		exit(1);
	}
}

// Manejo de lectura
void	ft_handle_lecture(t_pipex *pipex, char **split)
{
	if (ft_strcmp(split[0], "<") != 0)
	{
		pipex->infile = open(split[1], O_RDONLY);
		if (pipex->infile < 0)
		{
			fprintf(stderr, "entro con: %s\n", split[1]);
			ft_errno(pipex->argv[pipex->i]);
			ft_free_pipex(&pipex);
			exit(1);
		}
	}
	else if (ft_strcmp(split[0], "<<") != 0)
	{
		pipex->infile = ft_here_doc(split[1]);
		if (pipex->infile < 0)
		{
			ft_errno(pipex->argv[pipex->i]);
			ft_free_pipex(&pipex);
			exit(1);
		}
	}
}

// Manejo de redirecciones
void	ft_handle_redirection(t_pipex *pipex, char **split)
{
	if (ft_strcmp(split[0], ">") != 0)
	{
		pipex->outfile = open(split[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipex->outfile < 0)
		{
			ft_errno(pipex->argv[pipex->i]);
			ft_free_pipex(&pipex);
			exit(1);
		}
	}
	else if (ft_strcmp(split[0], ">>") != 0)
	{
		pipex->outfile = open(split[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		printf("\nsplit[1]: %s\n", split[1]);
		if (pipex->outfile < 0)
		{
			ft_errno(pipex->argv[pipex->i]);
			ft_free_pipex(&pipex);
			exit(1);
		}
		printf("\noutfile FD antes de dup2 justo despues de abrir el archivo: %d\n", pipex->outfile);
	}
}*/

int	ft_here_doc(char *delimiter)
{
	char	*line;
	int		temp_pipe[2];

	if (pipe(temp_pipe) < 0)
		ft_perror("Pipex error: Pipe\n");
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		write(temp_pipe[WRITE], line, ft_strlen(line));
		free(line);
	}
	close(temp_pipe[WRITE]);
	return (temp_pipe[READ]);
}
