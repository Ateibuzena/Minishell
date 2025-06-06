/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:27:13 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/20 19:57:49 by azubieta         ###   ########.fr       */
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
	t_command	*cmd;

	cmd = pipex->exec->commands[pipex->i];
	ft_execute_builtin_or_error(pipex, cmd);
	ft_execute_external(pipex, cmd);
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
		if (ft_setup_pipe(pipex) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		pid = ft_fork_process();
		if (pid == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (pid == 0)
			ft_child_process(pipex);
		ft_close_fds(pipex);
		pipex->i++;
	}
	return (pid);
}
