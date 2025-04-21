/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_middle_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:30:00 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/21 21:30:52 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"
/*
static void ft_middle_fork(t_pipex *pipex, char **env)
{
    fprintf(stderr, "\nEntro en middle fork con pipex->argv[pipex->cmd]: %s\n", pipex->argv[pipex->cmd]);
    close(pipex->pipes[pipex->count - 1][WRITE]);
    close(pipex->pipes[pipex->count][READ]);

    dup2(pipex->pipes[pipex->count - 1][READ], STDIN_FILENO);
    close(pipex->pipes[pipex->count - 1][READ]);

    dup2(pipex->pipes[pipex->count][WRITE], STDOUT_FILENO);
    close(pipex->pipes[pipex->count][WRITE]);

    fprintf(stderr, "Hijo del middle proceso\n");
    print_open_fds();
    ft_execute(pipex, env);
    //fprintf(stderr, "--------------------------------------------------\n");
    exit(1);
}

static void ft_close_fds(t_pipex *pipex)
{
    close(pipex->pipes[pipex->count - 1][READ]);
    close(pipex->pipes[pipex->count][WRITE]);
    fprintf(stderr, "Padre de middle proceso\n");
    print_open_fds();
    fprintf(stderr, "-----------------------------------------------\n");
}

void ft_middle_process(t_pipex *pipex, char **env)
{
    char **split;

    split = NULL;
    while (pipex->count <= pipex->n - 1)
    {  
        ft_create_pipe(pipex);
        while (pipex->i < pipex->size && !ft_strchr(pipex->argv[pipex->i], '|'))
        {
            split = ft_split(pipex->argv[pipex->i], ' ');
            ft_handle_lecture(pipex, split);
            ft_handle_redirection(pipex, split);
            ft_is_command(pipex, split[0]);
            ft_freedouble(split);
            pipex->i++;
        }
        
        pipex->pids[pipex->count] = fork();
        if (pipex->pids[pipex->count] == -1)
            return (ft_perror("Fork error: middle process\n"));
        else if (pipex->pids[pipex->count] == 0)
        {
            ft_middle_fork(pipex, env);
            fprintf(stderr, "-----------------------------------------------\n");
        }
        else
        {
            ft_close_fds(pipex);
            pipex->status = ft_waitpid(pipex->pids[pipex->count]);
        }
        pipex->i += 1;
        pipex->count += 1;
    }
}
*/