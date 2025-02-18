/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:37:22 by azubieta          #+#    #+#             */
/*   Updated: 2025/02/18 16:19:04 by azubieta         ###   ########.fr       */
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

static int ft_handle_redirection(t_pipex *pipex, int *infile, int *outfile)
{
	int i = 0;
	int cmd = 0;
	
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
			cmd = i + 2;
        i++;
    }
	return (cmd);
}
// Función para el primer proceso
void ft_first_process(t_pipex *pipex, char **env)
{
    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
    int i = pipex->i;

    ft_create_pipe(pipex);
	i = ft_handle_redirection(pipex, &infile, &outfile);
    

	// 🔥 IMPORTANTE: Aquí va el fork(), fuera del while
	pipex->pids[pipex->count] = fork();
	if (pipex->pids[pipex->count] == -1)
	{
		perror("Error en fork");
		return ;
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
        ft_execute_cmd(pipex, pipex->argv[i - 2], env, NULL);
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
}


// Función para los procesos intermedios
int ft_middle_process(t_pipex *pipex, char **env)
{
    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
	int i = pipex->i;

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
            return (-1);
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
            ft_execute_cmd(pipex, pipex->argv[i - 2], env, NULL);
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
    return (i);
}

// Función para el último proceso
void ft_last_process(t_pipex *pipex, char **env)
{
    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;
	int i = pipex->i;

	if (pipex->count >= pipex->n)
		return ;
	// Reservar memoria para la nueva pipe (sin usar new_pipe)
	ft_create_pipe(pipex);

	// Manejo de redirecciones
	int cmd = 0;
    int len = ft_strlen_double(pipex->argv);

	while (i < len)
    {
        char **split = ft_split(pipex->argv[i], ' ');
		
        // Manejo de redirecciones
        if (ft_strcmp(split[0], "<") != 0)
        {
            infile = open(split[1], O_RDONLY);
            if (infile < 0) ft_errno(pipex->argv[i]);
        }
        else if (ft_strcmp(split[0], ">") != 0)
        {
            outfile = open(split[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (outfile < 0) ft_errno(pipex->argv[i]);
        }
        else if (ft_strcmp(split[0], ">>") != 0)
        {
            outfile = open(split[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (outfile < 0) ft_errno(pipex->argv[i]);
        }
        else if (ft_strcmp(split[0], "<<") != 0)
        {
            infile = ft_here_doc(split[1]);
            if (infile < 0) ft_errno(pipex->argv[i]);
        }
        else
			cmd = i + 2;
        i++;
    }
    // Crear el último proceso con fork
    pipex->pids[pipex->count] = fork();
    if (pipex->pids[pipex->count] == -1) {
        perror("fork failed");
        return ;
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
		ft_execute_cmd(pipex, pipex->argv[cmd - 2], env, NULL);
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

