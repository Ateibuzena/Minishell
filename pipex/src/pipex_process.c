/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:37:22 by azubieta          #+#    #+#             */
/*   Updated: 2025/02/22 18:42:09 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

static void ft_create_pipe(t_pipex *pipex)
{
	// Reservar memoria para una nueva pipe
	pipex->pipes = realloc(pipex->pipes, sizeof(int *) * (pipex->count + 1));
	if (!pipex->pipes)
	{
		perror("Error al redimensionar pipes");
		return ;
	}

	// Asignar memoria para la nueva pipe
	pipex->pipes[pipex->count] = malloc(sizeof(int) * 2);
	if (!pipex->pipes[pipex->count])
	{
		perror("Error al asignar memoria a pipes[count]");
		return ;
	}

	// Crear la pipe directamente en pipex->pipes[pipex->i]
	if (pipe(pipex->pipes[pipex->count]) < 0)
	{
		perror("Error al crear pipe");
		return ;
	}

}

// Manejo de lectura
static void ft_handle_lecture(t_pipex *pipex, char **split)
{
    if (ft_strcmp(split[0], "<") != 0)
    {
        pipex->infile = open(split[1], O_RDONLY);
        if (pipex->infile < 0)
            (ft_errno(pipex->argv[pipex->i]), ft_free_pipex(&pipex), exit(1));
    }
    else if (ft_strcmp(split[0], "<<") != 0)
    {
        pipex->infile = ft_here_doc(split[1]);
        if (pipex->infile < 0)
            (ft_errno(pipex->argv[pipex->i]), ft_free_pipex(&pipex), exit(1));
    }
}

// Manejo de redirecciones
static void ft_handle_redirection(t_pipex *pipex, char **split)
{
    if (ft_strcmp(split[0], ">") != 0)
    {
        pipex->outfile = open(split[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (pipex->outfile < 0)
        (ft_errno(pipex->argv[pipex->i]), ft_free_pipex(&pipex), exit(1));
    }
    else if (ft_strcmp(split[0], ">>") != 0)
    {
        pipex->outfile = open(split[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (pipex->outfile < 0)
            (ft_errno(pipex->argv[pipex->i]), ft_free_pipex(&pipex), exit(1));
    }
}

// Función para el primer proceso
void ft_first_process(t_pipex *pipex, char **env)
{
    char    **split;
    fprintf(stderr, "entro en first process padre n: %d\n", pipex->n);
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
        pipex->i++;
    }
	pipex->pids[pipex->count] = fork();
	if (pipex->pids[pipex->count] == -1)
		return (ft_perror("Fork error: first process\n"));
	if (pipex->pids[pipex->count] == 0) // Proceso hijo
    {
        fprintf(stderr, "entro en first process hijo n: %d\n", pipex->n);
        close(pipex->pipes[pipex->count][READ]);
        // Redirigir entrada
        if (pipex->infile != STDIN_FILENO)
        {
            dup2(pipex->infile, STDIN_FILENO);
            close(pipex->infile);
        }
        // Redirigir salida
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
        // Ejecutar
        if ((pipex->cmd >= 0) && ft_is_builtins(pipex->argv[pipex->cmd]))
        {
            split = ft_split(pipex->argv[pipex->cmd], ' ');
            ft_execute_builtins(split, pipex->history, (t_Env **)env);
            ft_freedouble(split);
        }
        else if ((pipex->cmd >= 0) && !ft_is_builtins(pipex->argv[pipex->cmd]))
            ft_execute_cmd(pipex, pipex->argv[pipex->cmd], env, NULL);
        fprintf(stderr, "salgo first process hijo n: %d\n", pipex->n);
        exit(1);
    }
    //close(pipex->pipes[pipex->count][READ]);
    if (pipex->infile != STDIN_FILENO)
        close(pipex->infile);
    if (pipex->outfile == STDOUT_FILENO && (pipex->n != 0))
        close(pipex->pipes[pipex->count][WRITE]);
    else if (pipex->outfile != STDOUT_FILENO)
        close(pipex->outfile);
	// ✅ El padre espera a que el hijo termine
    waitpid(pipex->pids[pipex->count], NULL, 0);
    fprintf(stderr, "salgo first process padre n: %d\n", pipex->n);
    pipex->i += 1;
	pipex->count += 1;
}


// Función para los procesos intermedios
void ft_middle_process(t_pipex *pipex, char **env)
{
    char **split;
    fprintf(stderr, "entro en midel process padre: %d\n", pipex->n);
    split = NULL;
    while (pipex->count < pipex->n - 1)
    {   
        ft_create_pipe(pipex);
        while (pipex->i < pipex->size && !ft_strchr(pipex->argv[pipex->i], '|'))
        {
            split = ft_split(pipex->argv[pipex->i], ' ');
            ft_handle_lecture(pipex, split);
            ft_handle_redirection(pipex, split);
            if ((ft_strcmp(split[0], "<") == 0) && (ft_strcmp(split[0], "<<") == 0)
                    && (ft_strcmp(split[0], ">") == 0) && (ft_strcmp(split[0], ">>") == 0))
                pipex->cmd = pipex->i;
            pipex->i++;
        }
        pipex->pids[pipex->count] = fork();
        if (pipex->pids[pipex->count] == -1)
            return (ft_perror("Fork error: Middle process"));
        if (pipex->pids[pipex->count] == 0)
        {
            fprintf(stderr, "mideel process en hijo: %d\n", pipex->n);
            close(pipex->pipes[pipex->count][READ]);
            // Redirigir entrada
			if (pipex->infile != STDIN_FILENO)
			{
                close(pipex->infile);
                dup2(pipex->infile, STDIN_FILENO);
            }	
			else
            {
				dup2(pipex->pipes[pipex->count - 1][READ], STDIN_FILENO);
                close(pipex->pipes[pipex->count - 1][READ]);
            }
			// Redirigir salida	
			if (pipex->outfile != STDOUT_FILENO)
			{
                dup2(pipex->outfile, STDOUT_FILENO);
                close(pipex->outfile);
            }
			else
            {
				dup2(pipex->pipes[pipex->count][WRITE], STDOUT_FILENO);
                close(pipex->pipes[pipex->count][WRITE]);

            }
            // Ejecutar
            if (ft_is_builtins(pipex->argv[pipex->cmd]))
            {
                split = ft_split(pipex->argv[pipex->cmd], ' ');
                ft_execute_builtins(split, pipex->history, (t_Env **)env);
                ft_freedouble(split);
            }
            else
                ft_execute_cmd(pipex, pipex->argv[pipex->cmd], env, NULL);
            fprintf(stderr, "salgo middel process hijo: %d\n", pipex->n);
            exit(1);
        }
        //close(pipex->pipes[pipex->count][READ]);
		if (pipex->infile != STDIN_FILENO)
			close(pipex->infile);
        else
            close(pipex->pipes[pipex->count - 1][READ]);
		if (pipex->outfile != STDOUT_FILENO)
			close(pipex->outfile);
        else
		    close(pipex->pipes[pipex->count][WRITE]);

		// ✅ El padre espera a que el hijo termine
		waitpid(pipex->pids[pipex->count], NULL, 0);
        
		pipex->i += 1;
		pipex->count += 1;
    }
    fprintf(stderr, "salgo middel proces padre: %d\n", pipex->n);
}

// Función para el último proceso
void ft_last_process(t_pipex *pipex, char **env)
{
    fprintf(stderr, "entro last process padre: %d\n", pipex->n);
	if (pipex->count >= pipex->n)
    {
        fprintf(stderr, "salgo directamente de last process: %d\n", pipex->n);
        //fprintf(stderr, "\ntoy aqui = count = %d, n = %d\n", pipex->count, pipex->n);
        return ;
    }

	// Manejo de redirecciones
	while (pipex->i < pipex->size)
    {
        char **split = NULL;
        split = ft_split(pipex->argv[pipex->i], ' ');
        // Manejo de redirecciones
        if (ft_strcmp(split[0], "<") != 0)
        {
            pipex->infile = open(split[1], O_RDONLY);
            if (pipex->infile < 0)
                (ft_errno(pipex->argv[pipex->i]), ft_free_pipex(&pipex), exit(1));
        }
        else if (ft_strcmp(split[0], "<<") != 0)
        {
            pipex->infile = ft_here_doc(split[1]);
            if (pipex->infile < 0)
                (ft_errno(pipex->argv[pipex->i]), ft_free_pipex(&pipex), exit(1));
        }
        else if (ft_strcmp(split[0], ">") != 0)
        {
            pipex->outfile = open(split[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (pipex->outfile < 0)
                (ft_errno(pipex->argv[pipex->i]), ft_free_pipex(&pipex), exit(1));
        }
        else if (ft_strcmp(split[0], ">>") != 0)
        {
            pipex->outfile = open(split[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (pipex->outfile < 0)
                (ft_errno(pipex->argv[pipex->i]), ft_free_pipex(&pipex), exit(1));
        }
        else
			pipex->cmd = pipex->i;
        ft_freedouble(split);
        pipex->i++;
    }
    char **split = NULL;
    // Crear el último proceso con fork
    pipex->pids[pipex->count] = fork();
    if (pipex->pids[pipex->count] == -1)
        return (ft_perror("Fork error: Last process"));
    if (pipex->pids[pipex->count] == 0)
    {  
        fprintf(stderr, "entro last process hijo: %d\n", pipex->n);
        // Redirigir entrada
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
		// Redirigir salida
		if (pipex->outfile != STDOUT_FILENO)
        {
            dup2(pipex->outfile, STDOUT_FILENO);
            close(pipex->outfile);
        }
		// Ejecutar
        if (ft_is_builtins(pipex->argv[pipex->cmd]))
        {
            split = ft_split(pipex->argv[pipex->cmd], ' ');
            ft_execute_builtins(split, pipex->history, (t_Env **)env);
            ft_freedouble(split);
        }
        else
            ft_execute_cmd(pipex, pipex->argv[pipex->cmd], env, NULL);
        fprintf(stderr, "salgo last process hijo: %d\n", pipex->n);
        exit(1);
    }
    //close(pipex->pipes[pipex->count - 1][READ]);
	if (pipex->infile != STDIN_FILENO)
        close(pipex->infile);
    else
        close(pipex->pipes[pipex->count - 1][READ]);
    if (pipex->outfile != STDOUT_FILENO)
		close(pipex->outfile);

	// ✅ El padre espera a que el hijo termine
	waitpid(pipex->pids[pipex->count], NULL, 0);
    fprintf(stderr, "salgo last process padre: %d\n", pipex->n);
	pipex->i += 1;
	pipex->count += 1;
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

