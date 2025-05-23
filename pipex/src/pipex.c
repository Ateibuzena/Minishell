/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:56:26 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/23 12:36:14 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

static int	ft_waitpid(pid_t *last_pid)
{
	pid_t		pid;
	int			status;
	int			last_status;

	last_status = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == (*last_pid))
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		pid = wait(&status);
	}
	return (last_status);
}

static void	ft_init_pipex(t_pipex *pipex, t_Env **env, t_History *history)
{
	pipex->i = 0;
	pipex->len = 0;
	pipex->prev_fd = -1;
	pipex->fd[READ] = -1;
	pipex->fd[WRITE] = -1;
	pipex->history = history;
	pipex->env = env;
	pipex->exec = NULL;
	pipex->env_array = NULL;
}

int	ft_pipex(char **argv, t_Env **env, t_History *history)
{
	t_pipex		pipex;

	if (!argv || !argv[0])
		return (ft_perror("Pipex error: No input\n"), ft_freedouble(argv), 1);
	ft_init_pipex(&pipex, env, history);
	pipex.exec = ft_parse_commands(argv);
	if (!pipex.exec)
	{
		g_exit = 1;
		return (ft_perror("Pipex error: NULL exec\n"), 1);
	}
	pipex.env_array = ft_envtoarray((*env));
	if (!pipex.env_array)
	{
		ft_free_executor(pipex.exec);
		g_exit = 1;
		return (ft_perror("Pipex error: NULL env_array\n"), 1);
	}
	pipex.last_pid = ft_process_pipeline(&pipex);
	pipex.last_status = ft_waitpid(&(pipex.last_pid));
	ft_free_executor(pipex.exec);
	ft_freedouble(pipex.env_array);
	return (pipex.last_status);
}
