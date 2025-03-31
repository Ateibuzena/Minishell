/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:32:39 by azubieta          #+#    #+#             */
/*   Updated: 2025/03/31 20:49:25 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

char	*ft_find_env_value(const char *key, char **env, size_t len)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, len))
			return (env[i] + len);
		i++;
	}
	return (NULL);
}

char	*ft_find_executable(char **paths, char *command)
{
	char	*full_path;
	char	*temp_path;
	int		i;

	if (!paths || !command)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp_path, command);
		free(temp_path);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	ft_resolve_cmd(t_pipex *pipex, char *argv, char **env, char **pathname)
{
	pipex->commands = ft_split(argv, ' ');
	if (!pipex->commands || !pipex->commands[0])
		(ft_perror(argv), ft_perror(": command not found\n"),
			ft_free_pipex(&pipex), exit(127));
	if (ft_strchr(argv, '/'))
	{
		*pathname = pipex->commands[0];
		if (access((*pathname), X_OK) != 0)
			(ft_perror("pipex: "), ft_perror(argv),
				ft_perror(": No such file or directory\n"),
				ft_free_pipex(&pipex), ft_freedouble(pathname), exit(127));
	}
	else
	{
		pipex->found_way = ft_find_env_value("PATH=", env, 5);
		if (!pipex->found_way)
			(ft_perror("pipex: "),
				ft_perror(argv), ft_perror(": No such file or directory\n"),
				ft_free_pipex(&pipex), exit(127));
		pipex->clean_paths = ft_split(pipex->found_way, ':');
		*pathname = ft_find_executable(pipex->clean_paths, pipex->commands[0]);
		if (!(*pathname))
			(ft_perror(argv), ft_perror(": command not found\n"),
				ft_free_pipex(&pipex), ft_freedouble(pathname), exit(127));
	}
}

void	ft_execute_cmd(t_pipex *pipex, char *argv, char **env, char *pathname)
{
	fprintf(stderr, "\nEntro en execute_cmd con argv: %s\n", argv);
	fprintf(stderr, "\n");
	if (!argv || !argv[0] || argv[0] == ' ' || !env)
	{
		(ft_perror(argv), ft_perror(": command not found\n"));
		(ft_free_pipex(&pipex), exit(127));
	}
	ft_resolve_cmd(pipex, argv, env, &pathname);
	ft_close_pipes(pipex);
	if (execve(pathname, pipex->commands, env) == -1)
	{
		if (errno == EACCES)
		{
			(ft_perror("pipex: "), ft_perror(argv));
			(ft_perror(": permission denied\n"), ft_free_pipex(&pipex));
			(free(pathname), exit(126));
		}
		else
		{
			(ft_perror(pipex->commands[0]), ft_perror(": command not found\n"));
			(ft_free_pipex(&pipex), free(pathname), exit(127));
		}
	}
}

void	ft_execute(t_pipex *pipex, char **env)
{
	char	**split;

	split = NULL;
	printf("\nEntro en execute con pipex->argv[pipex->cmd]: %s\n", pipex->argv[pipex->cmd]);
	if ((pipex->cmd >= 0) && ft_is_builtins(pipex->argv[pipex->cmd]))
	{
		split = ft_split(pipex->argv[pipex->cmd], ' ');
		ft_execute_builtins(split, pipex->history, (t_Env **)env);
		ft_freedouble(split);
	}
	else if ((pipex->cmd >= 0) && !ft_is_builtins(pipex->argv[pipex->cmd]))
		ft_execute_cmd(pipex, pipex->argv[pipex->cmd], env, NULL);
}
