/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azubieta <azubieta@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:43:13 by azubieta          #+#    #+#             */
/*   Updated: 2025/04/22 20:32:16 by azubieta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipexft.h"

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
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
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

char *ft_strjoin_free(char *s1, char *s2)
{
    char *result;
    size_t len1, len2;

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
    free(s1);  // Libera la primera cadena
    return (result);
}

char **env_to_array(t_Env *env)
{
	t_Env *tmp = env;
	int count = 0;
	char **env_array;

	// 1. Contamos cuántas variables hay
	while (tmp)
	{
		if (tmp->key && tmp->value)
			count++;
		tmp = tmp->next;
	}

	// 2. Reservamos espacio (+1 para el NULL final)
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);

	// 3. Rellenamos el array
	tmp = env;
	int i = 0;
	while (tmp)
	{
		if (tmp->key && tmp->value)
		{
			int len = strlen(tmp->key) + strlen(tmp->value) + 2; // '=' y '\0'
			env_array[i] = malloc(sizeof(char) * len);
			if (!env_array[i])
			{
				// Manejo de error: liberar todo lo anterior
				while (i-- > 0)
					free(env_array[i]);
				free(env_array);
				return (NULL);
			}
			strcpy(env_array[i], tmp->key);
			strcat(env_array[i], "=");
			strcat(env_array[i], tmp->value);
			i++;
		}
		tmp = tmp->next;
	}
	env_array[i] = NULL; // NULL final para execve

	return env_array;
}
