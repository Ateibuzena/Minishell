/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:56:26 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/22 05:17:52 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

/*int	ft_pipex(char **input, char **env, t_History *history)
{
	t_pipex	*pipex;
	int		status;

	int i = 0;
	while (input[i])
	{
		fprintf(stderr, "input[%d]: %s\n", i, input[i]);
		i++;
	}
	status = 0;
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (ft_perror("Malloc error: pipex\n"), 1);
	ft_memset(pipex, 0, sizeof(t_pipex));
	ft_init(pipex, input, history);
	ft_first_process(pipex, env);
	ft_middle_process(pipex, env);
	ft_last_process(pipex, env);
	status = pipex->status;
	fprintf(stderr, "\nStatus: %d\n", status);
	ft_free_pipex(&pipex);
	return (status);
}*/

void	free_partial_executor(t_executor *exec)
{
	int	i, j;

	if (!exec)
		return;
	for (i = 0; i < exec->count; i++)
	{
		t_command *cmd = exec->commands[i];
		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		if (cmd->cmd)
		{
			for (j = 0; cmd->cmd[j]; j++)
				free(cmd->cmd[j]);
			free(cmd->cmd);
		}
		free(cmd);
	}
	free(exec->commands);
	free(exec);
}


static char	*extract_file(char *token)
{
	char	*res;

	res = ft_strchr(token, ' ');
	if (!res)
		return (NULL);
	return (ft_strdup(res + 1));
}

t_command	*init_command(void)
{
	t_command *cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_command));
	cmd->cmd = malloc(sizeof(char *) * 256);
	if (!cmd->cmd)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

t_executor	*parse_commands(char **argv)
{
	t_executor	*exec;
	t_command	*curr;
	int			i, cmd_idx;

	exec = malloc(sizeof(t_executor));
	if (!exec)
		return (NULL);  // primer malloc crítico
	exec->commands = malloc(sizeof(t_command *) * 256); // max comandos
	if (!exec->commands)
	{
		free(exec);
		return (NULL);  // liberar lo anterior
	}
	exec->count = 0;
	curr = init_command();
	if (!curr)
	{
		free_partial_executor(exec);
		return (NULL);
	}
	cmd_idx = 0;

	i = 0;
	while (argv[i])
	{
		if (ft_strncmp(argv[i], "|", 1) == 0)
		{
			curr->cmd[cmd_idx] = NULL;
			exec->commands[exec->count++] = curr;
			curr = malloc(sizeof(t_command));
			ft_memset(curr, 0, sizeof(t_command));
			curr->cmd = malloc(sizeof(char *) * 256);
			cmd_idx = 0;
		}
		else if (ft_strncmp(argv[i], "<<", 2) == 0)
		{
			curr->heredoc = extract_file(argv[i]);
		}
		else if (ft_strncmp(argv[i], "<", 1) == 0 && ft_strncmp(argv[i], "<<", 2) != 0)
			curr->infile = extract_file(argv[i]);
		else if (ft_strncmp(argv[i], ">>", 2) == 0 && ft_strncmp(argv[i], ">", 1) != 0)
		{
			curr->outfile = extract_file(argv[i]);
			curr->append = 1;
		}
		else if (ft_strncmp(argv[i], ">", 1) == 0)
		{
			curr->outfile = extract_file(argv[i]);
			curr->append = 0;
		}
		else
		{
			char **split = ft_split(argv[i], ' ');
			for (int k = 0; split[k]; k++)
				curr->cmd[cmd_idx++] = ft_strdup(split[k]);
			ft_freedouble(split);
		}
		i++;
	}
	curr->cmd[cmd_idx] = NULL;
	exec->commands[exec->count++] = curr;
	return (exec);
}

char *ft_strjoin_free(char *s1, char *s2)
{
    char *result;
    size_t len1, len2;

    if (!s1 || !s2)
        return (NULL);
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    result = malloc(len1 + len2 + 1);
    if (!result)
        return (NULL);
    ft_memcpy(result, s1, len1);
    ft_memcpy(result + len1, s2, len2);
    result[len1 + len2] = '\0';
    free(s1);  // Libera la primera cadena
    return (result);
}


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

void	free_executor(t_executor *exec)
{
	int	i, j;

	if (!exec)
		return;
	i = 0;
	while (i < exec->count)
	{
		t_command *cmd = exec->commands[i];

		if (cmd->infile)
			free(cmd->infile);
		if (cmd->outfile)
			free(cmd->outfile);
		if (cmd->cmd)
		{
			j = 0;
			while (cmd->cmd[j])
			{
				free(cmd->cmd[j]);
				j++;
			}
			free(cmd->cmd);
		}
		free(cmd);
		i++;
	}
	free(exec->commands);
	free(exec);
}

static char **env_to_array(t_Env *env)
{
	t_Env *tmp = env;
	int count = 0;
	char **env_array;

	// 1. Contamos cuántas variables hay
	while (tmp)
	{
		if (tmp->key && tmp->value)
			count++;
		tmp = tmp->next;
	}

	// 2. Reservamos espacio (+1 para el NULL final)
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);

	// 3. Rellenamos el array
	tmp = env;
	int i = 0;
	while (tmp)
	{
		if (tmp->key && tmp->value)
		{
			int len = strlen(tmp->key) + strlen(tmp->value) + 2; // '=' y '\0'
			env_array[i] = malloc(sizeof(char) * len);
			if (!env_array[i])
			{
				// Manejo de error: liberar todo lo anterior
				while (i-- > 0)
					free(env_array[i]);
				free(env_array);
				return (NULL);
			}
			strcpy(env_array[i], tmp->key);
			strcat(env_array[i], "=");
			strcat(env_array[i], tmp->value);
			i++;
		}
		tmp = tmp->next;
	}
	env_array[i] = NULL; // NULL final para execve

	return env_array;
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



int	ft_pipex(char **argv, t_Env *env, t_History *history)
{
	t_executor	*exec;

	if (!argv || !argv[0])
	return (ft_perror("Pipex error: No input\n"), 1);
	exec = parse_commands(argv);
	execute_pipeline(exec, env, history);
	
	free_executor(exec);
	return (0);
}
