/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanin <chanin@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 21:47:26 by azubieta          #+#    #+#             */
/*   Updated: 2025/05/28 17:16:02 by chanin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static char	*ft_read_fd(int fd, char *buffer)
{
	char	*temp;
	char	*chunk;
	int		bytes;

	chunk = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!chunk)
		return (NULL);
	bytes = 1;
	while (!ft_strchr_getnextline(buffer, '\n') && bytes > 0)
	{
		bytes = read(fd, chunk, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			return (ft_free(chunk));
		}
		chunk[bytes] = '\0';
		temp = buffer;
		buffer = ft_strjoin_getnextline(buffer, chunk);
		free(temp);
		if (!buffer)
			return (ft_free(chunk));
	}
	free(chunk);
	return (buffer);
}

static char	*ft_extract_line(char *buffer)
{
	int		i;
	char	*line;
	int		len;

	if (!buffer || buffer[0] == '\0')
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	len = i;
	if (buffer[i] == '\n')
		len++;
	line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*ft_update_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new = malloc((ft_strlen_getnextline(buffer) - i + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i++;
	while (buffer[i])
		new[j++] = buffer[i++];
	new[j] = '\0';
	free(buffer);
	buffer = NULL;
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (buffer)
		{
			free(buffer);
			buffer = NULL;
		}
		return (NULL);
	}
	buffer = ft_read_fd(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_extract_line(buffer);
	buffer = ft_update_buffer(buffer);
	return (line);
}
