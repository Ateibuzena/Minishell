/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:37:22 by azubieta          #+#    #+#             */
/*   Updated: 2025/02/17 20:54:24 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"
/*
static void	ft_redirection(t_pipex *pipex, char **env)
{
	int	outfile;
	int	infile;

	infile = open(pipex->argv[0], O_RDONLY); //split por el espacio, segundo argumento
	outfile = open(pipex->argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0 || infile < 0)
		(ft_perror("Open failed: outfile\n"),
			ft_free_pipex(&pipex), exit(EXIT_FAILURE));
	ft_child_process(infile, outfile);
	ft_execute_cmd(pipex, argv[2], env, NULL);
}*/


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

static void ft_create_pipe(t_pipex *pipex)
{
	// Reservar memoria para una nueva pipe
	pipex->pipes = realloc(pipex->pipes, sizeof(int *) * (pipex->count + 1));
	if (!pipex->pipes)
	{
		perror("Error al redimensionar pipes");
		exit(1);
	}

	// Asignar memoria para la nueva pipe
	pipex->pipes[pipex->count] = malloc(sizeof(int) * 2);
	if (!pipex->pipes[pipex->count])
	{
		perror("Error al asignar memoria a pipes[count]");
		exit(1);
	}

	// Crear la pipe directamente en pipex->pipes[pipex->i]
	if (pipe(pipex->pipes[pipex->count]) < 0)
	{
		perror("Error al crear pipe");
		exit(1);
	}

}

static int ft_handle_redirection(t_pipex *pipex, int *infile, int *outfile)
{
	int i = 0;
	
    int len = ft_strlen_double(pipex->argv);

	while (i < len && !ft_strchr(pipex->argv[i], '|'))
    {
        char **split = ft_split(pipex->argv[i], ' ');
		
        // Manejo de redirecciones
        if (ft_strcmp(split[0], "<") != 0)
        {
            (*infile) = open(split[1], O_RDONLY);
            if ((*infile) < 0) ft_errno(pipex->argv[i]);
        }
        else if (ft_strcmp(split[0], ">") != 0)
        {
            (*outfile) = open(split[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if ((*outfile) < 0) ft_errno(pipex->argv[i]);
        }
        else if (ft_strcmp(split[0], ">>") != 0)
        {
            (*outfile) = open(split[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if ((*outfile) < 0) ft_errno(pipex->argv[i]);
        }
        else if (ft_strcmp(split[0], "<<") != 0)
        {
            (*infile) = ft_here_doc(split[1]);
            if ((*infile) < 0) ft_errno(pipex->argv[i]);
        }
        else
        {
			//ft_handle_redirection(pipex, infile, outfile);
			i += 2;
			break ;
        }
        i++;
    }
	return (i);
}
// Función para el primer proceso
void ft_first_process(t_pipex *pipex, char **env)
{
    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
    int i = 0;

    fprintf(stderr, "[PRIMER PROCESO] entro en first_process con  i : %d e pipex->i: %d\n", i, pipex->i);

    ft_create_pipe(pipex);
	i = ft_handle_redirection(pipex, &infile, &outfile);
    

	// 🔥 IMPORTANTE: Aquí va el fork(), fuera del while
	pipex->pids[pipex->count] = fork();
	if (pipex->pids[pipex->count] == -1)
	{
		perror("Error en fork");
		exit(1);
	}
	if (pipex->pids[pipex->count] == 0) // Proceso hijo
    {
        // Redirigir entrada
        if (infile != STDIN_FILENO)
        {
            dup2(infile, STDIN_FILENO);
            close(infile);
        }
        // Redirigir salida
		if (outfile == STDOUT_FILENO && (pipex->n != 0))  // Solo si no hay redirección a archivo y no es un solo comando
			dup2(pipex->pipes[pipex->count][WRITE], STDOUT_FILENO);
		else
			dup2(outfile, STDOUT_FILENO);

		// Cerrar descriptores ya duplicados
		close(pipex->pipes[pipex->count][WRITE]);
		if (outfile != STDOUT_FILENO) 
			close(outfile);

        // Ejecutar comando
		fprintf(stderr, "[PRIMER PROCESO] CON  i : %d e pipex->i: %d\n", i - 2, pipex->i);
		fprintf(stderr, "[PRIMER PROCESO] CON  count : %d \n", pipex->count);
        ft_execute_cmd(pipex, pipex->argv[i - 2], env, NULL);
        exit(1);
    }

    // 🔥 El padre cierra lo que no necesita
    if (infile != STDIN_FILENO)
        close(infile);
    if (outfile != STDOUT_FILENO)
        close(outfile);
    close(pipex->pipes[pipex->count][WRITE]); // Cerrar el extremo de escritura del pipe

	// ✅ El padre espera a que el hijo termine
    waitpid(pipex->pids[pipex->count], NULL, 0);

	pipex->i = i;
	pipex->count += 1;
    fprintf(stderr, "[PRIMER PROCESO] padre salgo de first_process con  i : %d e pipex->i: %d y count : %d \n", i, pipex->i, pipex->count);
}


// Función para los procesos intermedios
int ft_middle_process(t_pipex *pipex, char **env)
{
    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
	int i = pipex->i;

    fprintf(stderr, "[PROCESOS INTERMEDIOS] entro en middle_process con  i : %d e pipex->i: %d\n", i, pipex->i);

    while (pipex->count < pipex->n - 1)
    {   
        // Reservar memoria para la nueva pipe (sin usar new_pipe)
        ft_create_pipe(pipex);

        // Manejo de redirecciones
        i = ft_handle_redirection(pipex, &infile, &outfile);

        // 🔥 Fork para el proceso intermedio
        pipex->pids[pipex->count] = fork();
        if (pipex->pids[pipex->count] == -1)
        {
            perror("Error en fork");
            exit(1);
        }
        
        if (pipex->pids[pipex->count] == 0)  // Proceso hijo
        {
            // Redirigir entrada
			if (infile != STDIN_FILENO)  // Solo si no hay redirección de archivo
				dup2(infile, STDIN_FILENO);
			else
				dup2(pipex->pipes[pipex->count - 1][READ], STDIN_FILENO);
			// Cerrar descriptores ya duplicados
			close(pipex->pipes[pipex->count - 1][READ]);
			if (infile != STDIN_FILENO) 
				close(infile);
				
            // 🔥 Escribir en la nueva pipe
			if (outfile != STDOUT_FILENO)  // Solo si no hay redirección de archivo
				dup2(outfile, STDOUT_FILENO);
			else
				dup2(pipex->pipes[pipex->count][WRITE], STDOUT_FILENO);
			// Cerrar descriptores ya duplicados
			close(pipex->pipes[pipex->count][WRITE]);
			if (outfile != STDOUT_FILENO) 
				close(outfile);
    
            // Cerrar extremos no usados
            close(pipex->pipes[pipex->count][READ]); // No se lee de la nueva pipe

            // Ejecutar comando
			fprintf(stderr, "[PROCESOS INTERMEDIOS] CON  i : %d e pipex->i: %d\n", i - 2, pipex->i);
			fprintf(stderr, "[PROCESOS INTERMEDIOS] CON  pipex->count: %d\n", pipex->count);
            ft_execute_cmd(pipex, pipex->argv[i - 2], env, NULL);
            exit(1);
        }
		// 🔥 El padre cierra lo que no necesita
		if (infile != STDIN_FILENO)
			close(infile);
		if (outfile != STDOUT_FILENO)
			close(outfile);
		close(pipex->pipes[pipex->count][WRITE]); // Cerrar el extremo de escritura del pipe
        close(pipex->pipes[pipex->count - 1][READ]); // Ya no necesita leer de la pipe anterior

		// ✅ El padre espera a que el hijo termine
		waitpid(pipex->pids[pipex->count], NULL, 0);
		pipex->i = i;
		pipex->count += 1;
        
    }
	fprintf(stderr, "[PROCESOS INTERMEDIOS] padre salgo de middle_process con i : %d e pipex->i: %d pipex->count: %d\n", i, pipex->i, pipex->count);
    return (i);
}

// Función para el último proceso
void ft_last_process(t_pipex *pipex, char **env)
{
    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
    int i = pipex->i;

	fprintf(stderr, "[ULTIMO PROCESO] entro en last_process con i : %d e pipex->i: %d\n", i, pipex->i);
	if (pipex->count >= pipex->n)
		return ;
	// Reservar memoria para la nueva pipe (sin usar new_pipe)
	ft_create_pipe(pipex);

	// Manejo de redirecciones
	i = ft_handle_redirection(pipex, &infile, &outfile);
	fprintf(stderr, "[ULTIMO PROCESO] outfile: %d infile: %d\n", outfile, infile);
	
    // Crear el último proceso con fork
    pipex->pids[pipex->count] = fork();
    if (pipex->pids[pipex->count] == -1) {
        perror("fork failed");
        exit(1);
    }

    if (pipex->pids[pipex->count] == 0) {  // Proceso hijo
        
        // Redirigir entrada
		if (infile != STDIN_FILENO)  // Solo si no hay redirección de archivo
			dup2(infile, STDIN_FILENO);
		else
			dup2(pipex->pipes[pipex->count - 1][READ], STDIN_FILENO);
		// Cerrar descriptores ya duplicados
		close(pipex->pipes[pipex->count - 1][READ]);
		if (infile != STDIN_FILENO) 
			close(infile);
			
		// 🔥 Escribir en la nueva pipe
		if (outfile != STDOUT_FILENO)  // Solo si no hay redirección de archivo
			dup2(outfile, STDOUT_FILENO);
		if (outfile != STDOUT_FILENO) 
			close(outfile);

		// Ejecutar comando
		fprintf(stderr, "[ULTIMO PROCESO] CON  i : %d e pipex->i: %d\n", i - 2, pipex->i);
		fprintf(stderr, "[ULTIMO PROCESO] CON cpunt: %d\n", pipex->count);
		ft_execute_cmd(pipex, pipex->argv[i - 2], env, NULL);
		exit(1);
    }

    // 🔥 El padre cierra lo que no necesita
	if (infile != STDIN_FILENO)
		close(infile);
	if (outfile != STDOUT_FILENO)
		close(outfile);
	close(pipex->pipes[pipex->count - 1][READ]); // Ya no necesita leer de la pipe anterior

	// ✅ El padre espera a que el hijo termine
	waitpid(pipex->pids[pipex->count], NULL, 0);
	
	pipex->i += 1;
	pipex->count += 1;
	fprintf(stderr, "[ULTIMO PROCESO] padre salgo de last_process con  i : %d e pipex->i: %d y cpunt: %d\n", i, pipex->i , pipex->count);
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

