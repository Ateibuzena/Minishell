/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:37:22 by azubieta          #+#    #+#             */
/*   Updated: 2025/02/11 19:48:49 by azubieta         ###   ########.fr       */
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
/*
void	ft_first_process(t_pipex *pipex, char **env)
{
	fprintf(stderr, "entro en first_process\n");
	int infile = STDIN_FILENO;
	int	i;
	int len;

	i = 0;
	len = ft_strlen_double(pipex->argv);
	while (i < len && !ft_strchr(pipex->argv[i], '|'))
	{
		// Si es un here_doc
		if (ft_strchr(pipex->argv[i], '<') && ft_strchr(pipex->argv[i + 1], '<')) // Aquí detectamos '<<'
		{
			if (infile != STDIN_FILENO)
				close(infile); // Cerrar entrada anterior

			// Llamamos a la función ft_here_doc con el delimitador
			infile = ft_here_doc(pipex->argv[i + 1]);
			if (infile < 0) // Si hay un error al crear el here_doc
			{
				ft_errno(pipex->argv[i]);
				ft_free_pipex(&pipex);
				exit(1);
			}
			i++;  // Pasamos al siguiente argumento
		}
		// Si es una redirección
		if (ft_strchr(pipex->argv[i], '>'))
		{
			if (infile != STDIN_FILENO)
				close(infile); // Cerrar entrada anterior
			// Si es ">>" (append)
			if (ft_strchr(pipex->argv[i], '>') && !ft_strchr(pipex->argv[i], '<'))
				infile = open(pipex->argv[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				infile = open(pipex->argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else if (ft_strchr(pipex->argv[i], '<'))  // Si es una redirección de entrada "<"
		{
			if (infile != STDIN_FILENO)
				close(infile); // Cerrar entrada anterior
			infile = open(pipex->argv[i + 1], O_RDONLY);
		}

		if (infile < 0)
		{
			ft_errno(pipex->argv[i]);
			ft_free_pipex(&pipex);
			exit(1);
		}
		else if (ft_strchr(pipex->argv[i], '|'))  // Si es un pipe "|"
		{
			// Aquí podrías manejar el caso de los pipes si es necesario
			break;
		}
		else  // Si es un comando, salimos del bucle
		{
			break;
		}
		i++;
	}
	pipex->i = i;
	pipex->pids[pipex->count] = fork();
	fprintf(stderr, "count en first process: %d\n", pipex->count);
	if (pipex->pids[pipex->count] < 0)
		(ft_free_pipex(&pipex), exit(1));
	pipex->count += 1;
	if (pipex->pids[pipex->count - 1] == 0)
	{
		close(pipex->pipes[pipex->count - 1][READ]);
		ft_child_process(infile, pipex->pipes[pipex->count - 1][WRITE]);
		fprintf(stderr, "commando %s\n", pipex->argv[i]);
		ft_execute_cmd(pipex, pipex->argv[i], env, NULL);
		fprintf(stderr, "salgo de first_process\n");
	}
	fprintf(stderr, "padre salgo de first_process\n");
	close(pipex->pipes[pipex->count - 1][WRITE]);
}*/


void	ft_first_process(t_pipex *pipex, char **env)
{
	fprintf(stderr, "entro en first_process\n");
	int infile = STDIN_FILENO;
	int outfile = STDOUT_FILENO;
	int outfile2;
	char	**split2;
	int	i;
	int len;

	i = 0;
	len = ft_strlen_double(pipex->argv);
	while (i < len && !ft_strchr(pipex->argv[i], '|'))
	{
		char	**split;
		split = ft_split(pipex->argv[i], ' ');
		if (ft_strcmp(split[0], "<")) //lectura
		{
			infile = open(split[1], O_RDONLY);
			if (infile < 0)
			{
				ft_errno(pipex->argv[i]);
				ft_free_pipex(&pipex);
				exit(1);
			}
			fprintf(stderr, "ejecuté primer infile del pipeline\n");
			ft_freedouble(split);
			
		}
		else if (ft_strcmp(split[0], "<<")) //here_doc
		{
			infile = ft_here_doc(split[1]);
			if (infile < 0)
			{
				ft_errno(pipex->argv[i]);
				ft_free_pipex(&pipex);
				exit(1);
			}
			fprintf(stderr, "ejecuté primer here_doc del pipeline\n");
			ft_freedouble(split);
			
		}
		else if (ft_strcmp(split[0], ">")) //redireccion
		{
			outfile = open(split[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (outfile < 0)
			{
				ft_errno(pipex->argv[i]);
				ft_free_pipex(&pipex);
				exit(1);
			}
			fprintf(stderr, "ejecuté primer redireccion del pipeline\n");
			ft_freedouble(split);
		}
		else if (ft_strcmp(split[0], ">>")) //doble_redireccion
		{
			outfile = open(split[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (outfile < 0)
			{
				ft_errno(pipex->argv[i]);
				ft_free_pipex(&pipex);
				exit(1);
			}
			fprintf(stderr, "ejecuté primer doble redireccion del pipeline\n");
			ft_freedouble(split);
		}
		else
		{
			split2 = ft_split(pipex->argv[i + 1], ' ');
			if (ft_strcmp(split2[0], "<")) //lectura
			{
				outfile2 = open(split2[1], O_RDONLY);
				if (outfile2 < 0)
				{
					ft_errno(pipex->argv[i + 1]);
					ft_free_pipex(&pipex);
					exit(1);
				}
				fprintf(stderr, "ejecuté el infile de despues del comando\n");
				ft_freedouble(split2);
				
			}
			else if (ft_strcmp(split2[0], "<<")) //here_doc
			{
				outfile2 = ft_here_doc(split2[1]);
				if (outfile2 < 0)
				{
					ft_errno(pipex->argv[i + 1]);
					ft_free_pipex(&pipex);
					exit(1);
				}
				fprintf(stderr, "ejecuté el here_doc de despues del comando\n");
				ft_freedouble(split2);
				
			}
			else if (ft_strcmp(split2[0], ">")) //redireccion
			{
				outfile2 = open(split2[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (outfile2 < 0)
				{
					ft_errno(pipex->argv[i + 1]);
					ft_free_pipex(&pipex);
					exit(1);
				}
				fprintf(stderr, "ejecuté la redireccion de despues del comando\n");
				ft_freedouble(split2);
			}
			else if (ft_strcmp(split2[0], ">>")) //doble_redireccion
			{
				outfile2 = open(split2[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (outfile2 < 0)
				{
					ft_errno(pipex->argv[i + 1]);
					ft_free_pipex(&pipex);
					exit(1);
				}
				fprintf(stderr, "ejecuté la doble_redireccion de despues del comando\n");
				ft_freedouble(split2);
			}
			pipex->i = i;
			pipex->pids[pipex->count] = fork();
			fprintf(stderr, "count en first process: %d\n", pipex->count);
			if (pipex->pids[pipex->count] < 0)
				(ft_free_pipex(&pipex), exit(1));
			pipex->count += 1;
			if (pipex->pids[pipex->count - 1] == 0)
			{
				close(pipex->pipes[pipex->count - 1][READ]);
				if (!outfile2)
				{
					outfile2 = pipex->pipes[pipex->count - 1][WRITE];
					fprintf(stderr, "outfile2 = %d\n", outfile2);
					ft_child_process(infile, outfile2);
					fprintf(stderr, "commando %s\n", pipex->argv[i]);
					if (ft_is_builtins(split[0]))
					{
						fprintf(stderr, "commando %s\n", split[0]);
						ft_execute(split, pipex->history, (t_Env **)env);
						fprintf(stderr, "ejecuté primer builtin del pipeline\n");
					}
					else
					{
						fprintf(stderr, "commando %s\n", split[0]);
						ft_execute_cmd(pipex, pipex->argv[i], env, NULL);
						fprintf(stderr, "ejecuté primer cmd del pipeline\n");
					}
					fprintf(stderr, "salgo de first_process\n");
				}
				else
				{

					fprintf(stderr, "outfile2 = %d\n", outfile2);
					ft_child_process(infile, outfile2);
					fprintf(stderr, "commando %s\n", pipex->argv[i]);
					if (ft_is_builtins(split[0]))
					{
						fprintf(stderr, "commando %s\n", split[0]);
						ft_execute(split, pipex->history, (t_Env **)env);
						fprintf(stderr, "ejecuté primer builtin del pipeline\n");
					}
					else
					{
						fprintf(stderr, "commando %s\n", split[0]);
						ft_execute_cmd(pipex, pipex->argv[i], env, NULL);
						fprintf(stderr, "ejecuté primer cmd del pipeline\n");
					}
					fprintf(stderr, "salgo de pipex\n");
					ft_free_pipex(&pipex);
					exit(1);
				}
			}
			fprintf(stderr, "padre salgo de first_process\n");
			close(pipex->pipes[pipex->count - 1][WRITE]);
		}
		i++;
	}
	/*
	pipex->i = i;
	pipex->pids[pipex->count] = fork();
	fprintf(stderr, "count en first process: %d\n", pipex->count);
	if (pipex->pids[pipex->count] < 0)
		(ft_free_pipex(&pipex), exit(1));
	pipex->count += 1;
	if (pipex->pids[pipex->count - 1] == 0)
	{
		close(pipex->pipes[pipex->count - 1][READ]);
		ft_child_process(infile, pipex->pipes[pipex->count - 1][WRITE]);
		fprintf(stderr, "commando %s\n", pipex->argv[i]);
		ft_execute_cmd(pipex, pipex->argv[i], env, NULL);
		fprintf(stderr, "salgo de first_process\n");
	}
	fprintf(stderr, "padre salgo de first_process\n");
	close(pipex->pipes[pipex->count - 1][WRITE]);
	*/
}

int	ft_middle_process(t_pipex *pipex, char **env)
{
	// Manejar las redirecciones específicas para este proceso
    int infile = STDIN_FILENO;
    int len = ft_strlen_double(pipex->argv);
    int i = pipex->i;

	fprintf(stderr, "entro en middle process\n");
	pipex->pids[pipex->count] = fork();
	pipex->count += 1;
	fprintf(stderr, "count en middle process: %d\n", pipex->count);
	if (pipex->pids[pipex->count - 1] < 0)
		(ft_free_pipex(&pipex), exit(1));
	if (pipex->pids[pipex->count - 1] == 0)
	{
		while (i < len && !ft_strchr(pipex->argv[i], '|'))  // Mientras no lleguemos a un pipe
		{
			// Si es un here_doc
			if (ft_strchr(pipex->argv[i], '<') && ft_strchr(pipex->argv[i + 1], '<')) // Aquí detectamos '<<'
			{
				if (infile != STDIN_FILENO)
					close(infile); // Cerrar entrada anterior

				// Llamamos a la función ft_here_doc con el delimitador
				infile = ft_here_doc(pipex->argv[i + 1]);
				if (infile < 0) // Si hay un error al crear el here_doc
				{
					ft_errno(pipex->argv[i]);
					ft_free_pipex(&pipex);
					exit(1);
				}
				i++;  // Pasamos al siguiente argumento
			}
			// Si es una redirección
			else if (ft_strchr(pipex->argv[i], '>'))
			{
				if (infile != STDIN_FILENO)
					close(infile); // Cerrar entrada anterior
				// Si es ">>" (append)
				if (ft_strchr(pipex->argv[i], '>') && !ft_strchr(pipex->argv[i], '<'))
					infile = open(pipex->argv[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
				else
					infile = open(pipex->argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			}
			else if (ft_strchr(pipex->argv[i], '<'))  // Si es una redirección de entrada "<"
			{
				if (infile != STDIN_FILENO)
					close(infile); // Cerrar entrada anterior
				infile = open(pipex->argv[i + 1], O_RDONLY);
			}

			if (infile < 0)
			{
				ft_errno(pipex->argv[i]);
				ft_free_pipex(&pipex);
				exit(1);
			}
			else if (ft_strchr(pipex->argv[i], '|'))  // Si es un pipe "|"
			{
				// Aquí podrías manejar el caso de los pipes si es necesario
				break;
			}
			else  // Si es un comando, salimos del bucle
			{
				// Redirigir la entrada y salida usando ft_child_process
				if (i > 0 && i < pipex->n - 1) 
					ft_child_process(pipex->pipes[pipex->count - 2][READ], pipex->pipes[pipex->count - 1][WRITE]);
				else if (i > 0)
					ft_child_process(pipex->pipes[pipex->count - 2][READ], STDOUT_FILENO);
				else if (i < pipex->n - 1)
					ft_child_process(STDIN_FILENO, pipex->pipes[pipex->count - 1][WRITE]);
				
				// Luego cerramos los pipes después de redirigir
				if (i < pipex->n - 1)
					close(pipex->pipes[pipex->count - 1][READ]);
				fprintf(stderr, "commando %s\n", pipex->argv[i]);
				ft_execute_cmd(pipex, pipex->argv[i], env, NULL);
				fprintf(stderr, "salgo de middle_process\n");
			}
			i++;
		}
	}
	fprintf(stderr, "padre salgo de middle_process\n");
	close(pipex->pipes[pipex->count - 1][WRITE]);
	return (i);
}

void	ft_last_process(t_pipex *pipex, char **env)
{
    int infile = STDIN_FILENO;  // La entrada viene del último pipe o de un archivo
    int outfile = STDOUT_FILENO;  // La salida es inicialmente hacia la salida estándar (pantalla)
    int len = ft_strlen_double(pipex->argv);
    int i = pipex->i;

    fprintf(stderr, "entro en last_process\n");

    // Fork del último proceso
    pipex->pids[pipex->count] = fork();
    if (pipex->pids[pipex->count] < 0)
    {
        ft_free_pipex(&pipex);
        exit(1);
    }

    if (pipex->pids[pipex->count] == 0)  // Proceso hijo
    {
        // Procesar las redirecciones
        while (i < len)
        {
            if (ft_strchr(pipex->argv[i], '<') && ft_strchr(pipex->argv[i + 1], '<')) // Detectamos "here_doc"
            {
                if (infile != STDIN_FILENO)
                    close(infile);
                infile = ft_here_doc(pipex->argv[i + 1]);
                if (infile < 0)
                {
                    ft_errno(pipex->argv[i]);
                    ft_free_pipex(&pipex);
                    exit(1);
                }
                i++;  // Saltar al siguiente argumento
            }
            else if (ft_strchr(pipex->argv[i], '>'))  // Detectamos redirección de salida ">"
            {
                if (outfile != STDOUT_FILENO)  // Si ya hay un archivo de salida, lo cerramos
                    close(outfile);
                
                if (ft_strchr(pipex->argv[i], '>') && !ft_strchr(pipex->argv[i], '<'))  // Redirección de salida con append ">>"
                    outfile = open(pipex->argv[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                else  // Redirección de salida con truncado ">"
                    outfile = open(pipex->argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            }
            else if (ft_strchr(pipex->argv[i], '<'))  // Detectamos redirección de entrada "<"
            {
                if (infile != STDIN_FILENO)
                    close(infile);
                infile = open(pipex->argv[i + 1], O_RDONLY);
            }

            // Comprobamos si la apertura del archivo ha fallado
            if (infile < 0 || outfile < 0)
            {
                ft_errno(pipex->argv[i]);
                ft_free_pipex(&pipex);
                exit(1);
            }

            // Si hay un pipe, no necesitamos hacer nada en el último proceso, ya que es el último en la cadena
            if (ft_strchr(pipex->argv[i], '|'))
            {
                break;
            }
            else  // Comando a ejecutar
            {
				pipex->count += 1;
                // Redirigir entrada, no hay salida porque es el último proceso
                ft_child_process(infile, outfile);
				fprintf(stderr, "commando %s\n", pipex->argv[i]);
                ft_execute_cmd(pipex, pipex->argv[i], env, NULL);
                fprintf(stderr, "salgo de last_process\n");
                break;
            }
            i++;
        }
    }

    // En el proceso padre, cerrar el pipe de lectura
    fprintf(stderr, "padre salgo de last_process\n");
    close(pipex->pipes[pipex->count][READ]);
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

