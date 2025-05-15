/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:27:13 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/15 13:47:40 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

char	*ft_path_env(char **env)
{
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			return (*env + 5);
		env++;
	}
	return (NULL);
}

char	*ft_resolve_path(char *cmd, char **env)
{
	char	**paths;
	char	*path_env;
	char	*test;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_env = ft_path_env(env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		test = ft_strjoin(paths[i], "/");
		test = ft_strjoin_free(test, cmd);
		if (access(test, X_OK) == 0)
			return (ft_freedouble(paths), test);
		free(test);
		i++;
	}
	return (ft_freedouble(paths), NULL);
}

void	ft_execute(t_pipex *pipex)
{
	char		*path;
	t_command	*cmd;

	cmd = pipex->exec->commands[pipex->i];
	if (ft_is_builtins(cmd->cmd[0]))
	{
		signal(SIGINT, SIG_DFL);
		if (ft_execute_builtins(cmd->cmd, pipex->history, pipex->env))
			(ft_errno(cmd->cmd[0]), ft_free_pipex(pipex), exit(EXIT_FAILURE));
		ft_free_pipex(pipex);
		exit(EXIT_SUCCESS);
	}
	else
	{
		path = ft_resolve_path(cmd->cmd[0], pipex->env_array);
		if (!path)
		{
			(ft_perror("pipex: "), ft_perror(cmd->cmd[0]));
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
}

void	ft_child_process(t_pipex *pipex)
{
	int	infile;
	int	outfile;

	infile = ft_handle_input(pipex);
	outfile = ft_handle_output(pipex);
	ft_handle_dup2(pipex, infile, outfile);
	if (pipex->fd[0] != -1)
		close(pipex->fd[0]);
	if (pipex->fd[1] != -1)
		close(pipex->fd[1]);
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
	ft_execute(pipex);
	exit(EXIT_SUCCESS);
}

pid_t	ft_process_pipeline(t_pipex *pipex)
{
	pid_t	pid;

	while (pipex->i < pipex->exec->count)
	{
		pipex->fd[0] = -1;
		pipex->fd[1] = -1;
		if (pipex->i < pipex->exec->count - 1 && pipe(pipex->fd) == -1)
		{
			g_exit = 1;
			return (ft_perror("pipe\n"), EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			g_exit = 1;
			return (ft_perror("fork\n"), EXIT_FAILURE);
		}
		if (pid == 0)
			ft_child_process(pipex);
		if (pipex->prev_fd != -1)
			close(pipex->prev_fd);
		if (pipex->i < pipex->exec->count - 1)
		{
			close(pipex->fd[1]);
			pipex->prev_fd = pipex->fd[0];
		}
		pipex->i++;
	}
	return (pid);
}
