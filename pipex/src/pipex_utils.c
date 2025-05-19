/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:43:13 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/19 00:28:28 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

int	ft_count_vars(t_Env *env)
{
	int		count;

	count = 0;
	while (env)
	{
		if (env->key && env->value)
			count++;
		env = env->next;
	}
	return (count);
}

char	**ft_envtoarray(t_Env *env)
{
	char	**env_array;
	int		i;

	env_array = ft_calloc(sizeof(char *), ft_count_vars(env) + 1);
	if (!env_array)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->key && env->value)
		{
			env_array[i] = ft_calloc(sizeof(char),
					(ft_strlen(env->key) + ft_strlen(env->value) + 2));
			if (!env_array[i])
				return (ft_free_partialdouble(env_array, i + 1), NULL);
			ft_strcpy(env_array[i], env->key);
			ft_strcat(env_array[i], "=");
			ft_strcat(env_array[i], env->value);
			i++;
		}
		env = env->next;
	}
	return (env_array);
}

int	ft_here_doc(char *delimiter)
{
	char	*line;
	int		temp_pipe[2];

	printf("Pipex: Here_doc delimiter: '%s'\n", delimiter);
	if (pipe(temp_pipe) < 0)
		(ft_perror("Pipex error: Pipe (here_doc)"), exit(EXIT_FAILURE));
	while (1)
	{
		write(1, "here_doc> ", 10);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			ft_perror("Pipex error: Here_doc (unexpected EOF)");
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(temp_pipe[WRITE], line, ft_strlen(line));
		free(line);
	}
	close(temp_pipe[WRITE]);
	return (temp_pipe[READ]);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2);
	result[len1 + len2] = '\0';
	free(s1);
	return (result);
}

void	ft_cmd_not_found(t_pipex *pipex, char *cmd)
{
	if (!cmd)
	{
		ft_perror("pipex: ");
		ft_perror("command not found\n");
		ft_free_pipex(pipex);
		exit(EXIT_FAILURE);
	}
}
