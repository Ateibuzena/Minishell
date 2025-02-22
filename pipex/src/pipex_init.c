#include "../pipexft.h"

// Contar comandos
static void ft_count_cmd(t_pipex *pipex, char *input[])
{
	int i;

	i = 0;
	pipex->n = 0;
    while (input[i])
	{
        if (ft_strcmp(input[i], "|") != 0)
            pipex->n++;
		i++;
    }
    if (pipex->n)
		pipex->n += 1;
}

// Inicializar estructura pipex
void ft_init(t_pipex *pipex, char *input[], t_History *history)
{
	int i;

	i = 0;
    pipex->status = 0;
	pipex->cmd = -1;
    pipex->history = history;
    pipex->i = 0;
    pipex->count = 0;
	pipex->infile = STDIN_FILENO;
	pipex->outfile = STDOUT_FILENO;
	ft_count_cmd(pipex, input);
    
    // Reservar memoria para argv
    pipex->argv = (char **)malloc(sizeof(char *) * (ft_strlen_double(input) + 1));
    if (!pipex->argv)
    return (ft_perror("Malloc error: argv\n"), ft_free_pipex(&pipex), exit(EXIT_FAILURE));
    
    while (input[i])
	{
        pipex->argv[i] = ft_strdup(input[i]); // strdup evita malloc + strcpy manual
        if (!pipex->argv[i])
            return (ft_perror("Malloc error: argv[i]\n"), ft_free_pipex(&pipex), exit(EXIT_FAILURE));
		i++;
	}
    pipex->argv[i] = NULL;
    pipex->size = i;

    // Reservar memoria para los PIDs
    pipex->pids = (pid_t *)malloc(pipex->n * sizeof(pid_t));
    if (!pipex->pids)
        return (ft_perror("Malloc error: pids\n"), ft_free_pipex(&pipex), exit(EXIT_FAILURE));
}