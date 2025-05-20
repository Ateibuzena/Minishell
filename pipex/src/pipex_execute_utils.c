/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execute_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:48:49 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/20 19:57:24 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

int	ft_setup_pipe(t_pipex *pipex)
{
	if (pipex->i < pipex->exec->count - 1)
	{
		if (pipe(pipex->fd) == -1)
		{
			g_exit = 1;
			ft_perror("pipe\n");
			return (EXIT_FAILURE);
		}
	}
	else
	{
		pipex->fd[0] = -1;
		pipex->fd[1] = -1;
	}
	return (0);
}

pid_t	ft_fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		g_exit = 1;
		ft_perror("fork\n");
		return (EXIT_FAILURE);
	}
	return (pid);
}

void	ft_close_fds(t_pipex *pipex)
{
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
	if (pipex->i < pipex->exec->count - 1)
	{
		close(pipex->fd[1]);
		pipex->prev_fd = pipex->fd[0];
	}
}

void	ft_execute_builtin_or_error(t_pipex *pipex, t_command *cmd)
{
	if (!cmd->cmd || !cmd->cmd[0])
	{
		ft_perror("pipex: ");
		ft_perror("command not found\n");
		ft_free_pipex(pipex);
		exit(127);
	}
	if (ft_is_builtins(cmd->cmd[0]))
	{
		signal(SIGINT, SIG_DFL);
		if (ft_execute_builtins(cmd->cmd, pipex->history, pipex->env))
		{
			ft_errno(cmd->cmd[0]);
			ft_free_pipex(pipex);
			exit(EXIT_FAILURE);
		}
		ft_free_pipex(pipex);
		exit(EXIT_SUCCESS);
	}
}

void	ft_execute_external(t_pipex *pipex, t_command *cmd)
{
	char	*path;

	path = ft_resolve_path(cmd->cmd[0], pipex->env_array);
	if (!path)
	{
		ft_perror("pipex: ");
		ft_perror(cmd->cmd[0]);
		ft_perror(": command not found\n");
		ft_free_pipex(pipex);
		exit(127);
	}
	signal(SIGINT, SIG_DFL);
	execve(path, cmd->cmd, pipex->env_array);
	ft_errno(cmd->cmd[0]);
	ft_free_pipex(pipex);
	exit(EXIT_FAILURE);
}
