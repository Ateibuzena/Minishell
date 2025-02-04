/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:43:13 by azubieta          #+#    #+#             */
/*   Updated: 2025/01/27 19:10:33 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

void	ft_init(t_pipex *pipex, char *input[])
{
	pipex->count = 0;
	pipex->status = 0;
    
	/*CONTAR COMANDOS*/

	pipex->n = 0;
    int i = 0;

    // Recorremos la cadena y contamos las pipes
    while (input[i])
	{
        if (ft_strcmp(input[i], "|") != 0)
            pipex->n++;
        i++;
    }
    // Sumamos 1 a las pipes para contar los comandos
	if (pipex->n)
    	pipex->n += 1;
	else if (!pipex->n)
	{
		if (input[0][0] && input[0][0] == '<' && ft_strlen_double(input) == 1)
			pipex->n = 0;
		else if (input[0][0] && input[0][0] == '<' && ft_strlen_double(input) == 2)
			pipex->n = 1;
		else //modificar por ft_strlendouble(input) == 1????
			pipex->n = 1;
	}
	fprintf(stderr, "numero comandos: %d\n", pipex->n);

	/*CONTAR COMANDOS*/
	
	/*INICIALIZAR FLAGS HERE_DOC, REDIRECTION O CMD*/

	pipex->here_doc = 0;
	pipex->redirection = 0;
	pipex->cmd = 0;
	pipex->append = 0;
	pipex->truncate = 0;
	if (input[0][0] == '<' && input[0][1] == '<')
		pipex->here_doc = 1;
	else if (input[0][0] == '<' && input[0][1] != '<')
		pipex->redirection = 1;
	else
		pipex->cmd = 1;
	if (input[ft_strlen_double(input) - 1][0] == '>'
		&& input[ft_strlen_double(input) - 1][1] == '>')
		pipex->append = 1;
	else if (input[ft_strlen_double(input) - 1][0] == '>'
		&& input[ft_strlen_double(input) - 1][1] != '>')
		pipex->truncate = 1;
	
	fprintf(stderr, "pipex->here_doc = %d\n", pipex->here_doc);
    fprintf(stderr, "pipex->redirection = %d\n", pipex->redirection);
    fprintf(stderr, "pipex->cmd = %d\n", pipex->cmd);
    fprintf(stderr, "pipex->append = %d\n", pipex->append);
    fprintf(stderr, "pipex->truncate = %d\n", pipex->truncate);
	
	/*INICIALIZAR FLAGS HERE_DOC, REDIRECTION O CMD*/

	/*INICIALIZAR ARGV*/

	int len = 0;

	if (pipex->here_doc || pipex->redirection)
		len += 1;
	if (pipex->append || pipex->truncate)
		len += 1;
	len += pipex->n;

	pipex->argv = (char **)malloc(sizeof(char *) * (len + 1));
	if (!pipex->argv)
	{
		ft_perror("Malloc error: argv\n");
		ft_free_pipex(&pipex);
		exit(EXIT_FAILURE);
	}
	i = 0;
	int j = 0;
	while (input[i])
	{
		while (*(input[i]) == '<' || *(input[i]) == ' ')
			input[i]++;
		while (*(input[i]) == '|')
			input++;
		while (*(input[i]) == '>' || *(input[i]) == ' ')
			input[i]++;
		pipex->argv[j] = (char *)malloc(sizeof(char) * (ft_strlen(input[i]) + 1));
		if (!pipex->argv[j])
		{
			ft_perror("Malloc error: argv[i]\n");
			ft_free_pipex(&pipex);
			exit(EXIT_FAILURE);
		}
		pipex->argv[j] = ft_strcpy(pipex->argv[j], input[i]);
		i++;
		j++;
	}
	pipex->argv[j] = NULL;
	
	int k = 0;
    while (pipex->argv[k])
    {
        fprintf(stderr, "commads dentro pipex: %s\n", pipex->argv[k]);
        k++;
    }
	//ft_freedouble(input);

	/*INICIALIZAR ARGV*/
	
	pipex->pipes = (int **)malloc((pipex->n - 1) * sizeof(int *));
	if (!pipex->pipes)
		(ft_perror("Malloc failed: pipes\n"), ft_free_pipex(&pipex),
			exit(EXIT_FAILURE));
	while (pipex->count < pipex->n - 1)
	{
		pipex->pipes[pipex->count] = (int *)malloc(2 * sizeof(int));
		if (!pipex->pipes[pipex->count]
			|| pipe(pipex->pipes[pipex->count]) == -1)
			(ft_perror("Pipe error: pipes[i]\n"), ft_free_pipex(&pipex),
				exit(EXIT_FAILURE));
		(pipex->count)++;
	}
	pipex->pids = (pid_t *)malloc((pipex->n) * sizeof(pid_t));
	if (!pipex->pids)
		(ft_perror("Malloc failed: pids\n"), ft_free_pipex(&pipex),
			exit(EXIT_FAILURE));
	pipex->clean_paths = NULL;
	pipex->commands = NULL;
	fprintf(stderr, "salgo de init\n");
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
			ft_perror(": No such file or directory"));
	else if (errno == EACCES)
		(ft_perror("pipex: "), ft_perror(argument),
			ft_perror(": Permission denied"));
	else if (errno == ENOMEM)
		ft_perror("pipex: Out of memory");
	else if (errno == EINVAL)
		ft_perror("pipex: Invalid argument");
	else if (errno == EISDIR)
		ft_perror("pipex: Is a directory");
	else if (errno == EMFILE)
		ft_perror("pipex: Too many open files");
	else if (errno == ENFILE)
		ft_perror("pipex: Too many open files in system");
	else if (errno == EFAULT)
		ft_perror("pipex: Bad address");
	else if (errno == EROFS)
		ft_perror("pipex: Read-only file system");
	else if (errno == ETXTBSY)
		ft_perror("pipex: Text file busy");
	else
		ft_perror("pipex: Open failed");
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
