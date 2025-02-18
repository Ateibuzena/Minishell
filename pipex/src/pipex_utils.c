/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:43:13 by azubieta          #+#    #+#             */
/*   Updated: 2025/02/18 15:59:41 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

void ft_init(t_pipex *pipex, char *input[], t_History *history)
{
    //fprintf(stderr, "[DEBUG] Entro en init\n");
    pipex->status = 0;
    pipex->history = history;

    // Contar comandos (separar en función si se quiere modularizar más)
    pipex->n = 0;
    for (int i = 0; input[i]; i++) {
        if (ft_strcmp(input[i], "|") != 0)
            pipex->n++;
    }
    if (pipex->n) pipex->n += 1;

    //fprintf(stderr, "[DEBUG] Número de comandos: %d\n", pipex->n);
    
    // Inicializar flags
    pipex->here_doc = 0;
    pipex->redirection = 0;
    pipex->cmd = 0;
    pipex->append = 0;
    pipex->truncate = 0;
    
    // Reservar memoria para argv
    pipex->argv = (char **)malloc(sizeof(char *) * (ft_strlen_double(input) + 1));
    if (!pipex->argv)
        return (ft_perror("Malloc error: argv"), ft_free_pipex(&pipex), exit(EXIT_FAILURE));
    
    for (int i = 0; input[i]; i++) {
        pipex->argv[i] = strdup(input[i]); // strdup evita malloc + strcpy manual
        if (!pipex->argv[i])
            return (ft_perror("Malloc error: argv[i]"), ft_free_pipex(&pipex), exit(EXIT_FAILURE));
    }
    pipex->argv[ft_strlen_double(input)] = NULL;

    // Debug: imprimir comandos almacenados
    //for (int k = 0; pipex->argv[k]; k++)
    //    fprintf(stderr, "[DEBUG] Comando en pipex->argv[%d]: %s\n", k, pipex->argv[k]);
	/*
    // Gestión de pipes
    pipex->pipes = (pipex->n > 1) ? malloc((pipex->n - 1) * sizeof(int *)) : NULL;
    if (pipex->n > 1 && !pipex->pipes)
        return (ft_perror("Malloc failed: pipes"), ft_free_pipex(&pipex), exit(EXIT_FAILURE));

    for (int i = 0; i < pipex->n - 1; i++) {
        pipex->pipes[i] = malloc(2 * sizeof(int));
        if (!pipex->pipes[i] || pipe(pipex->pipes[i]) == -1) {
            ft_perror("Pipe error");
            ft_free_pipex(&pipex);
            exit(EXIT_FAILURE);
        }
    }*/

    // Reservar memoria para los PIDs
    pipex->pids = (pid_t *)malloc(pipex->n * sizeof(pid_t));
    if (!pipex->pids)
        return (ft_perror("Malloc failed: pids"), ft_free_pipex(&pipex), exit(EXIT_FAILURE));
    
    //fprintf(stderr, "[DEBUG] Salgo de init\n");
}

void	ft_close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->pipes)
	{
		while (i < pipex->n - 1)
		{
			close(pipex->pipes[i][READ]);
			close(pipex->pipes[i][WRITE]);
			i++;
		}
	}
}

void	ft_perror(const char *str)
{
	write(2, str, ft_strlen(str));
}

void	ft_errno(char *argument)
{
	if (errno == ENOENT)
		(ft_perror("pipex: "), ft_perror(argument),
			ft_perror(": No such file or directory\n"));
	else if (errno == EACCES)
		(ft_perror("pipex: "), ft_perror(argument),
			ft_perror(": Permission denied\n"));
	else if (errno == ENOMEM)
		ft_perror("pipex: Out of memory\n");
	else if (errno == EINVAL)
		ft_perror("pipex: Invalid argument\n");
	else if (errno == EISDIR)
		ft_perror("pipex: Is a directory\n");
	else if (errno == EMFILE)
		ft_perror("pipex: Too many open files\n");
	else if (errno == ENFILE)
		ft_perror("pipex: Too many open files in system\n");
	else if (errno == EFAULT)
		ft_perror("pipex: Bad address\n");
	else if (errno == EROFS)
		ft_perror("pipex: Read-only file system\n");
	else if (errno == ETXTBSY)
		ft_perror("pipex: Text file busy\n");
	else
		ft_perror("pipex: Open failed\n");
}

void	ft_free_pipex(t_pipex **pipex)
{
	int	i;

	if (!(*pipex))
		return ;
	i = 0;
	if ((*pipex)->pipes)
	{
		while (i < (*pipex)->n - 1 && (*pipex)->pipes[i])
		{
			close((*pipex)->pipes[i][READ]);
			close((*pipex)->pipes[i][WRITE]);
			free((*pipex)->pipes[i]);
			i++;
		}
		free((*pipex)->pipes);
	}
	if ((*pipex)->clean_paths)
		ft_freedouble((*pipex)->clean_paths);
	if ((*pipex)->commands)
		ft_freedouble((*pipex)->commands);
	if ((*pipex)->pids)
		free((*pipex)->pids);
	free((*pipex));
}
