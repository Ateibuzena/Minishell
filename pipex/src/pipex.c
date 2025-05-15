/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:56:26 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/14 22:05:48 by azubieta         ###   ########.fr       */
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

int	ft_pipex(char **argv, t_Env *env, t_History *history)
{
	pid_t		last_pid;
	int			last_status;
	t_pipex		pipex;

	if (!argv || !argv[0])
		return (ft_perror("Pipex error: No input\n"), ft_freedouble(argv), 1);
	pipex.i = 0;
	pipex.len = ft_strlen_double(argv);
	pipex.prev_fd = -1;
	pipex.env = &env;
	pipex.history = history;
	pipex.exec = ft_parse_commands(argv);
	if (!pipex.exec)
	{
		g_exit = 1;
		return (ft_perror("Pipex error: NULL exec\n"), 1);
	}
	pipex.env_array = ft_envtoarray(env);
	if (!pipex.env_array)
	{
		ft_free_executor(pipex.exec, pipex.len);
		g_exit = 1;
		return (ft_perror("Pipex error: NULL env_array\n"), 1);
	}	
	last_pid = ft_process_pipeline(&pipex);
	last_status = ft_waitpid(&last_pid);
	ft_free_executor(pipex.exec, pipex.len);
	ft_freedouble(pipex.env_array);
	return (last_status);
}
