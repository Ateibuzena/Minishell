/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:32:39 by azubieta          #+#    #+#             */
/*   Updated: 2025/02/07 20:57:49 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

int	ft_here_doc(char *delimiter)
{
	char	*line;
	int		temp_pipe[2];

	if (pipe(temp_pipe) < 0)
		ft_perror("Pipe error");
	while (1)
	{
		write(1, ">", 1);
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

char	*ft_find_env_value(const char *key, char **env, size_t len)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, len))
			return (env[i] + len);
		i++;
	}
	return (NULL);
}

char	*ft_find_executable(char **paths, char *command)
{
	char	*full_path;
	char	*temp_path;
	int		i;

	if (!paths || !command)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp_path, command);
		free(temp_path);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	ft_resolve_cmd(t_pipex *pipex, char *argv, char **env, char **pathname)
{
	pipex->commands = ft_split(argv, ' ');
	if (!pipex->commands || !pipex->commands[0])
		(ft_perror(argv), ft_perror(": command not found\n"),
			ft_free_pipex(&pipex), exit(127));
	if (ft_strchr(argv, '/'))
	{
		*pathname = pipex->commands[0];
		if (access((*pathname), X_OK) != 0)
			(ft_perror("pipex: "), ft_perror(argv),
				ft_perror(": No such file or directory\n"),
				ft_free_pipex(&pipex), ft_freedouble(pathname), exit(127));
	}
	else
	{
		pipex->found_way = ft_find_env_value("PATH=", env, 5);
		if (!pipex->found_way)
			(ft_perror("pipex: "),
				ft_perror(argv), ft_perror(": No such file or directory\n"),
				ft_free_pipex(&pipex), exit(127));
		pipex->clean_paths = ft_split(pipex->found_way, ':');
		*pathname = ft_find_executable(pipex->clean_paths, pipex->commands[0]);
		if (!(*pathname))
			(ft_perror(argv), ft_perror(": command not found\n"),
				ft_free_pipex(&pipex), ft_freedouble(pathname), exit(127));
	}
}

void	ft_execute_cmd(t_pipex *pipex, char *argv, char **env, char *pathname)
{
    fprintf(stderr, "Entro en execute_cmd con argv: %s\n", argv);

    if (!argv || !argv[0] || argv[0] == ' ')
    {
        ft_perror(argv);
        ft_perror(": command not found\n");
        ft_free_pipex(&pipex);
        exit(127);
    }

    ft_resolve_cmd(pipex, argv, env, &pathname);

    if (!pathname)  // Verificar que pathname no sea NULL
    {
        fprintf(stderr, "Error: pathname es NULL\n");
        ft_perror(argv);
        ft_perror(": command not found\n");
        ft_free_pipex(&pipex);
        exit(127);
    }

    if (!pipex->commands || !pipex->commands[0])  // Verificar que commands no sea NULL
    {
        fprintf(stderr, "Error: pipex->commands es NULL o está vacío\n");
        ft_free_pipex(&pipex);
        exit(127);
    }

    ft_close_pipes(pipex);

    fprintf(stderr, "Execve con pathname: %s y primer argumento: %s\n", pathname, pipex->commands[0]);
    fprintf(stderr, "pipex->commands antes de execve:\n");
	int i = 0;
	while (pipex->commands[i])
	{
		fprintf(stderr, "commands[%d]: %s\n", i, pipex->commands[i]);
		i++;
	}
	fprintf(stderr, "commands[%d]: (NULL)\n", i);
	if (!env) {
		fprintf(stderr, "ERROR: env es NULL\n");
		exit(1);
	}
	/*
	i = 0;
	while (env[i]) {
		fprintf(stderr, "env[%d]: %s\n", i, env[i]);
		i++;
	}*/

	/*char *args[3];
	args[0] = strdup("/usr/bin/cat");  // Copia la string en memoria segura
	args[1] = strdup("archivo.txt");   // Lo mismo con el argumento
	args[2] = NULL;

	fprintf(stderr, "Ejecutando execve con valores seguros\n");
	execve(args[0], args, env);
	fprintf(stderr, "execve falló: %s\n", strerror(errno));
	exit(1);*/
    if (execve(pathname, pipex->commands, env) == -1)
    {
        fprintf(stderr, "Execve falló: %s\n", strerror(errno));

        if (errno == EACCES)
        {
            ft_perror("pipex: ");
            ft_perror(argv);
            ft_perror(": Permission denied\n");
            ft_free_pipex(&pipex);
            free(pathname);
            exit(126);
        }
        else
        {
            ft_perror(pipex->commands[0]);
            ft_perror(": command not found\n");
            ft_free_pipex(&pipex);
            free(pathname);
            exit(127);
        }
    }
}
