/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:27:13 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/22 20:32:09 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

char *resolve_path(char *cmd, char **env)
{
	char	**paths;
	char	*path_env;
	char	*test;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));  // ya es una ruta válida

	// Busca la variable PATH en env
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			path_env = *env + 5;
			break;
		}
		env++;
	}
	if (!path_env)
		return (NULL); // No hay PATH

	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		test = ft_strjoin(paths[i], "/");
		test = ft_strjoin_free(test, cmd); // crea path completo y libera anterior
		if (access(test, X_OK) == 0)
		{
			ft_freedouble(paths);
			return (test);
		}
		free(test);
		i++;
	}
	ft_freedouble(paths);
	return (NULL); // No encontrado
}

void execute_pipeline(t_executor *exec, t_Env *env, t_History *history)
{
	int i;
    int fd[2];
    int prev_fd = -1;
    pid_t pid;
    char **env_array = env_to_array(env);
	
    if (!env_array)
    {
		perror("malloc");
        exit(EXIT_FAILURE);
    }
	fprintf(stderr, "exec->commands \n");
	fprintf(stderr, "exec->count %d\n", exec->count);
    i = 0;
    while (i < exec->count)
    {
        fd[0] = -1;
        fd[1] = -1;
        
        // Crear el pipe entre los comandos
        if (i < exec->count - 1 && pipe(fd) == -1)
        {
            perror("pipe");
            exit(1);
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        
        if (pid == 0)  // Proceso hijo
        {
            // Entrada: Redirección de archivo
            if (exec->commands[i]->infile || exec->commands[i]->heredoc)
            {
				int in;
				if (exec->commands[i]->heredoc)
					in = ft_here_doc(exec->commands[i]->heredoc);
				else
                	in = open(exec->commands[i]->infile, O_RDONLY);
                if (in < 0)
                {
                    ft_errno(exec->commands[i]->infile);
                    exit(1);  // Terminar si falla la entrada
                }
                if (dup2(in, STDIN_FILENO) < 0)  // Redirigir stdin
                {
                    perror("dup2 in");
                    exit(1);
                }
                close(in);
            }
            else if (prev_fd != -1)  // Si existe un archivo descriptor anterior (pipeline)
            {
                if (dup2(prev_fd, STDIN_FILENO) < 0)
                {
                    perror("dup2 prev_fd");
                    exit(1);
                }
            }

            // Salida: Redirección de archivo
            if (exec->commands[i]->outfile)
            {
                int out = open(exec->commands[i]->outfile,
                    O_WRONLY | O_CREAT | (exec->commands[i]->append ? O_APPEND : O_TRUNC), 0644);
                if (out < 0)
                {
                    ft_errno(exec->commands[i]->outfile);
                    exit(1);  // Terminar si falla la salida
                }
                if (dup2(out, STDOUT_FILENO) < 0)  // Redirigir stdout
                {
                    perror("dup2 out");
                    exit(1);
                }
                close(out);
            }
            else if (i < exec->count - 1)  // Si no hay archivo de salida, pero hay más comandos
            {
                if (dup2(fd[1], STDOUT_FILENO) < 0)  // Redirigir a pipe
                {
                    perror("dup2 fd[1]");
                    exit(1);
                }
            }

            // Cerrar descriptores no utilizados
            if (fd[0] != -1)
                close(fd[0]);
            if (fd[1] != -1)
                close(fd[1]);
            if (prev_fd != -1)
                close(prev_fd);

            // Ejecutar el comando
            if (ft_is_builtins(exec->commands[i]->cmd[0]))
            {
                if (ft_execute_builtins(exec->commands[i]->cmd, history, &env))
                {
                    ft_errno(exec->commands[i]->cmd[0]);
                    exit(1);
                }
                exit(0);
            }
            else
            {
                char *path = resolve_path(exec->commands[i]->cmd[0], env_array);
                if (!path)
                {
                    ft_perror("pipex: ");
                    ft_perror(exec->commands[i]->cmd[0]);
                    ft_perror(": command not found\n");
                    ft_freedouble(env_array);
                    exit(127);  // Comando no encontrado
                }
                execve(path, exec->commands[i]->cmd, env_array);
                ft_errno(exec->commands[i]->cmd[0]);
                ft_freedouble(env_array);
                exit(1);
            }
        }

        // Padre: Cerrar descriptores usados
        if (prev_fd != -1)
            close(prev_fd);
        if (i < exec->count - 1)
        {
            close(fd[1]);      // Cerrar escritura del pipe ya usado
            prev_fd = fd[0];   // Mantener la lectura para el siguiente comando
        }
        i++;
    }

    // Esperar a que todos los procesos hijos terminen
    while (wait(NULL) > 0);
}
