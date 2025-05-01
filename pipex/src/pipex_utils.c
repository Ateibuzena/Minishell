/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:43:13 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/01 23:02:10 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

static int	ft_count_vars(t_Env *env)
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

	env_array = malloc(sizeof(char *) * (ft_count_vars(env) + 1));
	i = 0;
	if (!env_array)
		return (NULL);
	while (env)
	{
		if (env->key && env->value)
		{
			env_array[i] = malloc(sizeof(char)
					* (ft_strlen(env->key) + ft_strlen(env->value) + 2));
			if (!env_array[i])
				return (ft_free_partialdouble(env_array, i), NULL);
			ft_strcpy(env_array[i], env->key);
			ft_strcat(env_array[i], "=");
			ft_strcat(env_array[i], env->value);
			i++;
		}
		env = env->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

int	ft_here_doc(char *delimiter)
{
	char	*line;
	int		temp_pipe[2];

	if (pipe(temp_pipe) < 0)
		ft_perror("Pipex error: Pipe\n");
	while (1)
	{
		write(1, "heredoc> ", 9);
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
