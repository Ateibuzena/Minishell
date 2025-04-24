/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:56:26 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/23 19:36:54 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

int	ft_pipex(char **argv, t_Env *env, t_History *history)
{
	t_executor	*exec;
	int			last_status = 0;
	pid_t		last_pid;

	if (!argv || !argv[0])
		return (ft_perror("Pipex error: No input\n"), 1);

	exec = parse_commands(argv);
	last_pid = execute_pipeline(exec, env, history);
	
	int status;
	pid_t pid;
	while ((pid = wait(&status)) > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
	}

	free_executor(exec);
	return (last_status);
}

